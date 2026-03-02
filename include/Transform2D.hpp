// TODO Ownership: Heitor

#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"

namespace engine {

class Basis2D {
public:
	Basis2D rotated(float angle) const;
	Basis2D scaled(float s) const;

public:		Vec2 i;
private:	float padding0;
public:		Vec2 j;
private:	float padding1;
};

class Matrix3 {
public:
	static const Matrix3 IDENTITY;

	Matrix3 transposed() const;
	Matrix3 operator*(const Matrix3&) const;


public:
	// ATTENTION: values are to be stored sequentially by columns.
	// Ie, {1.0, 2.0, 3.0} is a *column, not a row*.
	union {
		struct {Vec3 x, y, z;};
		struct {float a[9];};
	};
};

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
