#include "Quat.hpp"

#include "Vec3.hpp"
#include "math.h"

using namespace engine;

Quat Quat::Qrotation(const Vec3& axis, float angle) {
	float t = angle/2;
	Quat ret;
	ret.xyz = sin(t) * axis;
	ret.w = cos(t);
	return ret;
}

Quat Quat::conjugate() const {
	return {
		-x,
		-y,
		-z,
		w
	};
}

Quat Quat::normalized() const {
	return {xyzw.normalized()};
}

/*
Basis3D Quat::toRotationBasis() {
	return {
		// i
		1.0f - 2.0f*(y*y + z*z),
		2.0f * (x*y + w*z),
		2.0f * (x*z - w*y),
		0,
		// j
		2.0f * (x*y - w*z),
		1.0f - 2.0f * (x*x + z*z),
		2.0f * (y*z + w*x),
		0,
		// k
		2.0f * (x*z + w*y),
		2.0f * (y*z - w*x),
		1.0f - 2.0f * (x*x + y*y),
		0
	};
}
*/

Quat Quat::operator*(const Quat& q) const {
	return {
		w*q.x + x*q.w + y*q.z - z*q.y,
		w*q.y - x*q.z + y*q.w + z*q.x, 
		w*q.z + x*q.y - y*q.x + z*q.w, 
		w*q.w - x*q.x - y*q.y - z*q.z,
	};
}

Vec3 Quat::operator*(const Vec3& v) const {
	Quat q = {v.x, v.y, v.z, 0};
	q = (*this) * q * conjugate();
	return q.xyz;
}
