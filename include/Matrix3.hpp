#pragma once

#include "Vec3.hpp"

namespace engine {

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

}
