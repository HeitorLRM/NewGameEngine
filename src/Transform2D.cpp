#include "Transform2D.hpp"

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

