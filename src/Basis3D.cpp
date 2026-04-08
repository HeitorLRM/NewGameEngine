
#include "Basis3D.hpp"

using namespace engine;

Basis3D Basis3D::rotated(const Vec3& axis, float angle) const {
	return {
		i.rotated(axis,angle),
		padding0,
		j.rotated(axis,angle),
		padding1,
		k.rotated(axis, angle),
		padding2
	};
}

Basis3D Basis3D::scaled(float s) const {
	return {
		i*s,
		padding0,
		j*s,
		padding1,
		k*s,
		padding2
	};
}