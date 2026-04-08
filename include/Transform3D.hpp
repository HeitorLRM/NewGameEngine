#pragma once

#include "Basis3D.hpp"
#include "Matrix4.hpp"
#include "Vec3.hpp"

namespace engine {

class Transform3D {
public:
	void translate(Vec3 translation);
	void rotate(Vec3 axis, float angle);
	void scale(float s);

	Transform3D operator*(const Transform3D&) const;
	Vec3 operator*(const Vec3&) const;

public:
	union {
		struct {Matrix4 matrix = Matrix4::IDENTITY;};
		struct {Basis3D basis; Vec3 position;};
	};
};

}
