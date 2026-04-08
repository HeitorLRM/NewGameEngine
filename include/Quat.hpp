#pragma once

#include "Vec3.hpp"
#include "Vec4.hpp"

namespace engine {

class Quat {
public:
	static Quat Qrotation(const Vec3& axis, float angle);

	Quat conjugate() const;
	Quat normalized() const;
	Quat operator*(const Quat& other) const;
	Vec3 operator*(const Vec3& v) const;

public:
	union {
		struct{Vec4 xyzw;};
		struct{float x,y,z,w;};
		struct{Vec3 xyz;};
	};
};

}


