#include "Transform3D.hpp"
#include "Vec3.hpp"

using namespace engine;


void Transform3D::translate(Vec3 translation) {
	position += translation;
}

void Transform3D::rotate(Vec3 axis, float angle) {
	basis = basis.rotated(axis, angle);
}

void Transform3D::scale(float s) {
	basis = basis.scaled(s);
}

Transform3D Transform3D::operator*(const Transform3D& t) const {
	return {matrix * t.matrix};
}

Vec3 Transform3D::operator*(const Vec3& v) const {
	Vec4 v4 = {v.x, v.y, v.z, 1.0};
	v4 = matrix * v4;
	return {v4.x, v4.y, v4.z};
}
