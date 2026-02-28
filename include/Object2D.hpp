// TODO ownership: Heitor

#pragma once

#include "GameObject.hpp"
#include "Transform2D.hpp"

namespace engine {

class Object2D : public GameObject {
public:
	Transform2D& getTransform();
	const Transform2D& getTransform() const;
	const Transform2D& getGlobalTransform();

private:
	void mark_global_transform_dirty();

private:
	Transform2D transform;
	Transform2D global_transform;
	bool is_global_transform_dirty = false;
};

}

