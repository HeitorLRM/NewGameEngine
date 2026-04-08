#pragma once

#include "Vec3.hpp"

namespace engine {

class Basis3D {
public:
	Basis3D rotated(const Vec3& axis, float angle) const;
	Basis3D scaled(float s) const;

public:
	Vec3 i;
	float padding0;
	Vec3 j;
	float padding1;
	Vec3 k;
	float padding2;
};

}

