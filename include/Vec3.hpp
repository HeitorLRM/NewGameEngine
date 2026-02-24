// TODO ownership: Heitor

#pragma once

#include <ostream>
namespace engine {

class Vec3 {
public:
	Vec3();
	Vec3(float x, float y, float z);

	static const Vec3 ZERO;
	static const Vec3 UP;
	static const Vec3 DOWN;
	static const Vec3 LEFT;
	static const Vec3 RIGHT;
	static const Vec3 FORWARD;
	static const Vec3 BACK;

	bool operator==(const Vec3&) const;
	bool operator!=(const Vec3&) const;
	Vec3 operator+(const Vec3&) const;
	Vec3 operator-(const Vec3&) const;
	Vec3 operator-() const;
	Vec3 operator*(float) const;
	Vec3 operator*(const Vec3&) const;
	Vec3 operator/(float) const;
	Vec3 operator/(const Vec3&) const;
	Vec3& operator+=(const Vec3&);
	Vec3& operator-=(const Vec3&);
	Vec3& operator*=(float);
	Vec3& operator/=(float);

	bool is_normalized() const;
	float len() const;
	float len_squared() const;
	float distance(const Vec3&) const;
	float distance_squared(const Vec3&) const;
	float angle_with(const Vec3&) const; // in radians
	float dot(const Vec3&) const;
	Vec3 cross(const Vec3&) const;
	Vec3 lerp(const Vec3& to, float t) const;
	Vec3 direction_to(const Vec3&) const;
	Vec3 limited_len(float max_len) const;
	Vec3 move_toward(const Vec3& to, float step) const;
	Vec3 normalized() const;
	Vec3 rotated(const Vec3&, float) const; // in radians
	Vec3 reflected(const Vec3&) const;
	Vec3 projected(const Vec3&) const;
	Vec3 slide(const Vec3&) const;

public: 
	float x, y, z;
};

}

engine::Vec3 operator*(float, const engine::Vec3&);
std::ostream& operator<<(std::ostream& out, const engine::Vec3&);
