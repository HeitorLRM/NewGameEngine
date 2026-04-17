#include "Object3D.hpp"
#include "GameObject.hpp"
#include "Transform3D.hpp"

using namespace engine;

const std::string& Object3D::getResourceType() const {
	static const std::string RES_NAME = "Object3D";
	return RES_NAME;
}

Transform3D& Object3D::getTransform() {
	mark_global_transform_dirty();
	return transform;
}

const Transform3D& Object3D::getTransform() const{
	return transform;
}

const Transform3D& Object3D::getGlobalTransform() {
	if (!is_global_transform_dirty)
		return global_transform;

	
	Object3D* parent3D = dynamic_cast<Object3D*>(getParent());
	if (!parent3D)
		return transform;

	global_transform = parent3D->getGlobalTransform()*transform;

	is_global_transform_dirty = false;
	return global_transform;
}

void Object3D::mark_global_transform_dirty() {
	is_global_transform_dirty = true;
	
	for (auto& child : getChildren()) {
		if (Object3D* child3D = dynamic_cast<Object3D*>(child.get()))
			child3D->mark_global_transform_dirty();
	}
}

void Object3D::setParent(GameObject* parent) {
	mark_global_transform_dirty();
	return GameObject::setParent(parent);
}

