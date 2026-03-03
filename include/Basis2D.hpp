#pragma once

#include "Vec2.hpp"

namespace engine {

class Basis2D {
public:
	Basis2D rotated(float angle) const;
	Basis2D scaled(float s) const;

public:		
	Vec2 i;
	float padding0;
	Vec2 j;
	float padding1;
};

}

