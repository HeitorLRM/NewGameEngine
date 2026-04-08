#pragma once

#include "Vec4.hpp"

namespace engine {

class Matrix4 {
public:
	static const Matrix4 IDENTITY;

	Matrix4 inverse() const;
	Matrix4 t_inverse() const;
	Matrix4 transposed() const;
	Matrix4 operator*(const Matrix4&) const;
	Matrix4 operator*(float) const;
	Vec4 operator*(const Vec4&) const;

public:
	// ATTENTION: values are to be stored sequentially by columns.
	// Ie, {1.0, 2.0, 3.0, 4.0} is a *column, not a row*.
	union {
		struct {Vec4 x, y, z, w;};
		struct {float a[16];};
	};
};

}
