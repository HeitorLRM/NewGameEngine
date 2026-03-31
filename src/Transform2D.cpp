#include "Transform2D.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

using namespace engine;


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

Vec2 Transform2D::operator*(const Vec2& v) const {
	Vec3 v3 = {v.x, v.y, 1.0};
	v3 = matrix * v3;
	return {v3.x, v3.y};
}
