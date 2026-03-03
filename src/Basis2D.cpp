
#include "Basis2D.hpp"

using namespace engine;

Basis2D Basis2D::rotated(float angle) const {
	return {
		i.rotated(angle),
		padding0,
		j.rotated(angle),
		padding1
	};
}

Basis2D Basis2D::scaled(float s) const {
	return {
		i*s,
		padding0,
		j*s,
		padding1
	};
}