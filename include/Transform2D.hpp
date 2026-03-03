// TODO Ownership: Heitor

#pragma once

#include "Basis2D.hpp"
#include "Matrix3.hpp"
#include "Vec2.hpp"

namespace engine {

class Transform2D {
public:
	void translate(Vec2 translation);
	void rotate(float angle);
	void scale(float s);

	Transform2D operator*(const Transform2D&) const;

public:
	union {
		struct {Matrix3 matrix = Matrix3::IDENTITY;};
		struct {Basis2D basis; Vec2 position;};
	};
};

}
