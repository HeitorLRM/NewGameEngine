#include "Transform2D.hpp"

using namespace engine;

Basis2D Basis2D::rotated(float angle) const {
	Basis2D b;
	b.i = i.rotated(angle);
	b.j = j.rotated(angle);
	return b;
}

Basis2D Basis2D::scaled(float s) const {
	Basis2D b;
	b.i = i*s;
	b.j = j*s;
	return b;
}

const Matrix3 Matrix3::IDENTITY = {
	1,0,0,
	0,1,0,
	0,0,1
};

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

void Transform2D::translate(Vec2 translation) {
	position += translation;
}

void Transform2D::rotate(float angle) {
	basis = basis.rotated(angle);
}

void Transform2D::scale(float s) {
	basis = basis.scaled(s);
}

Transform2D Transform2D::operator*(const Transform2D& t) const {
	return {matrix * t.matrix};
}

