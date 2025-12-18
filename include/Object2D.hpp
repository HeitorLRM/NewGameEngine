// TODO ownership: Heitor

#pragma once

#include "GameObject.hpp"
#include "Vec2.hpp"

namespace engine {

class Object2D : public GameObject {
public:
	void setLocalPosition(const Vec2&);
	Vec2& getLocalPosition();
	Vec2 getGlobalPosition();

protected:
	Vec2 getParentGlobalPosition();

	Vec2 local_position;

};

}

