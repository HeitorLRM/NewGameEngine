#include "Matrix3.hpp"
#include "Vec3.hpp"

using namespace engine;

const Matrix3 Matrix3::IDENTITY = {
	1,0,0,
	0,1,0,
	0,0,1
};

Matrix3 Matrix3::inverse() const {
	float det = (
		a[0] * (a[4] * a[8] - a[7] * a[5]) -
		a[1] * (a[3] * a[8] - a[5] * a[6]) +
		a[2] * (a[3] * a[7] - a[4] * a[6])
	);
	float dinv = 1 / det;

	Matrix3 minv;
	minv.a[0] = (a[4] * a[8] - a[7] * a[5]);
	minv.a[1] = (a[2] * a[7] - a[1] * a[8]);
	minv.a[2] = (a[1] * a[5] - a[2] * a[4]);
	minv.a[3] = (a[5] * a[6] - a[3] * a[8]);
	minv.a[4] = (a[0] * a[8] - a[2] * a[6]);
	minv.a[5] = (a[3] * a[2] - a[0] * a[5]);
	minv.a[6] = (a[3] * a[7] - a[6] * a[4]);
	minv.a[7] = (a[6] * a[1] - a[0] * a[7]);
	minv.a[8] = (a[0] * a[4] - a[3] * a[1]);

	minv = minv * dinv;
	return minv;
}

Matrix3 Matrix3::transposed() const {
	return {
		a[0], a[3], a[6],
		a[1], a[4], a[7],
		a[2], a[5], a[8]
	};
}

Matrix3 Matrix3::operator*(const Matrix3& m) const {
	Matrix3 t = transposed();
	return {
		t.x.dot(m.x), t.y.dot(m.x), t.z.dot(m.x),
		t.x.dot(m.y), t.y.dot(m.y), t.z.dot(m.y),
		t.x.dot(m.z), t.y.dot(m.z), t.z.dot(m.z),
	};
}

Matrix3 Matrix3::operator*(float f) const {
	Matrix3 m;
	for (int i=0; i<9; i++) {
		m.a[i] = a[i] * f;
	}
	return m;
}

Vec3 Matrix3::operator*(const Vec3& v) const {
	return Vec3{
		v.dot(x),
		v.dot(y),
		v.dot(z)
	};
}

