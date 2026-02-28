// TODO ownership: Heitor

#include "Object2D.hpp"
#include "Transform2D.hpp"
#include <memory>

using namespace engine;

Transform2D& Object2D::getTransform() {
	mark_global_transform_dirty();
	return transform;
}

const Transform2D& Object2D::getTransform() const{
	return transform;
}

const Transform2D& Object2D::getGlobalTransform() {
	if (!is_global_transform_dirty)
		return global_transform;

	
	Object2D* parent2D = dynamic_cast<Object2D*>(getParent());
	if (!parent2D)
		return transform;

	global_transform = parent2D->getGlobalTransform()*transform;

	is_global_transform_dirty = false;
	return global_transform;
}

void Object2D::mark_global_transform_dirty() {
	is_global_transform_dirty = true;
	
	for (auto& child : getChildren()) {
		Object2D* child2D = dynamic_cast<Object2D*>(child.get());
		if (child2D)
			child2D->mark_global_transform_dirty();
	}
}

