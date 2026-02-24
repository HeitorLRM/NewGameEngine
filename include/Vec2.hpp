// TODO ownership: Heitor

#pragma once

#include <ostream>
namespace engine {

class Vec2 {
public:
	Vec2();
	Vec2(float x, float y);

	static const Vec2 ZERO;
	static const Vec2 UP;
	static const Vec2 DOWN;
	static const Vec2 LEFT;
	static const Vec2 RIGHT;

	bool operator==(const Vec2&) const;
	bool operator!=(const Vec2&) const;
	Vec2 operator+(const Vec2&) const;
	Vec2 operator-(const Vec2&) const;
	Vec2 operator-() const;
	Vec2 operator*(float) const;
	Vec2 operator*(const Vec2&) const;
	Vec2 operator/(float) const;
	Vec2 operator/(const Vec2&) const;
	Vec2& operator+=(const Vec2&);
	Vec2& operator-=(const Vec2&);
	Vec2& operator*=(float);
	Vec2& operator/=(float);

	bool is_normalized() const;
	float len() const;
	float len_squared() const;
	float distance(const Vec2&) const;
	float distance_squared(const Vec2&) const;
	float angle() const; // in radians
	float angle_with(const Vec2&) const; // in radians
	float dot(const Vec2&) const;
	float cross(const Vec2&) const;
	Vec2 lerp(const Vec2& to, float t) const;
	Vec2 direction_to(const Vec2&) const;
	Vec2 limited_len(float max_len) const;
	Vec2 move_toward(const Vec2& to, float step) const;
	Vec2 normalized() const;
	Vec2 orthogonal() const;
	Vec2 rotated(float) const; // in radians
	Vec2 reflected(const Vec2&) const;
	Vec2 projected(const Vec2&) const;
	Vec2 slide(const Vec2&) const;

public: 
	float x, y;
};

}

engine::Vec2 operator*(float, const engine::Vec2&);
std::ostream& operator<<(std::ostream& out, const engine::Vec2&);
