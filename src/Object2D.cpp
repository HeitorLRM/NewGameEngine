// TODO ownership: Heitor

#include "Object2D.hpp"
#include "Vec2.hpp"

using namespace engine;

void Object2D::setLocalPosition(const Vec2& position) {
	this->local_position = position;
}

Vec2& Object2D::getLocalPosition() {
	return local_position;
}

Vec2 Object2D::getGlobalPosition() {
	return getParentGlobalPosition() + local_position;
}

Vec2 Object2D::getParentGlobalPosition() {
	Object2D* parent2D = dynamic_cast<Object2D*>(getParent());

	if (!parent2D)
		return Vec2::ZERO;

	return parent2D->getGlobalPosition();
}
