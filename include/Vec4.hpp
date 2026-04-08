// TODO ownership: Heitor

#pragma once

#include "Vec3.hpp"

#include <ostream>

namespace engine {

class Vec4 {
public:
	static const Vec4 ZERO;

	bool operator==(const Vec4&) const;
	bool operator!=(const Vec4&) const;
	Vec4 operator+(const Vec4&) const;
	Vec4 operator-(const Vec4&) const;
	Vec4 operator-() const;
	Vec4 operator*(float) const;
	Vec4 operator*(const Vec4&) const;
	Vec4 operator/(float) const;
	Vec4 operator/(const Vec4&) const;
	Vec4& operator+=(const Vec4&);
	Vec4& operator-=(const Vec4&);
	Vec4& operator*=(float);
	Vec4& operator/=(float);

	bool is_normalized() const;
	float len() const;
	float len_squared() const;
	float angle_with(const Vec4&) const; // in radians
	float dot(const Vec4&) const;
	Vec4 cross(const Vec4&) const;
	Vec4 lerp(const Vec4& to, float t) const;
	Vec4 normalized() const;
	Vec4 rotated(const Vec4&, float) const; // in radians

public: 
	union {
		struct {float x, y, z, w;};
		struct {Vec3 xyz;};
	};
};

}

engine::Vec4 operator*(float, const engine::Vec4&);
std::ostream& operator<<(std::ostream& out, const engine::Vec4&);
