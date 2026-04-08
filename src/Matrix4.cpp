#include "Matrix4.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

using namespace engine;

const Matrix4 Matrix4::IDENTITY = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

/*
	Only applies to transform matrices, ie

	i.x, i.y, i.z, 0,
	j.x, j.y, j.z, 0,
	k.x, k.y, k.z, 0,
	T.x, T.y, T.z, 1

	aka

	basis		│0
	────────────┼─
	translation	│1


	Taken from https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
*/
Matrix4 Matrix4::t_inverse() const {
	Matrix4 m;

	const Vec3 t = {w.x, w.y, w.z};

	// vec / len = normalized. 
	// normalized / len = inverse of vec.
	m.x = x / x.len_squared();
	m.y = y / y.len_squared();
	m.z = z / z.len_squared();
	m.w = {0,0,0,1};
	m.x.w = -t.dot(m.x.xyz);
	m.y.w = -t.dot(m.y.xyz);
	m.z.w = -t.dot(m.z.xyz);

	m = m.transposed();

	return m;
}

Matrix4 Matrix4::transposed() const {
	return {
		a[0], a[4], a[8], a[12],
		a[1], a[5], a[9], a[13],
		a[2], a[6], a[10], a[14],
		a[3], a[7], a[11], a[15],
	};
}

Matrix4 Matrix4::operator*(const Matrix4& m) const {
	Matrix4 t = transposed();
	return {
		t.x.dot(m.x), t.y.dot(m.x), t.z.dot(m.x), t.w.dot(m.x),
		t.x.dot(m.y), t.y.dot(m.y), t.z.dot(m.y), t.w.dot(m.y),
		t.x.dot(m.z), t.y.dot(m.z), t.z.dot(m.z), t.w.dot(m.z),
		t.x.dot(m.w), t.y.dot(m.w), t.z.dot(m.w), t.w.dot(m.w),
	};
}

Matrix4 Matrix4::operator*(float f) const {
	Matrix4 m;
	for (int i=0; i<16; i++) {
		m.a[i] = a[i] * f;
	}
	return m;
}

Vec4 Matrix4::operator*(const Vec4& v) const {
	return Vec4{
		v.dot(x),
		v.dot(y),
		v.dot(z),
		v.dot(w)
	};
}

