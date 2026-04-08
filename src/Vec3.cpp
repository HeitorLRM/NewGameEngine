// TODO ownership: Heitor

#include "Vec3.hpp"
#include "Math.hpp"
#include "Quat.hpp"
#include <ostream>

using namespace engine;

const Vec3 Vec3::ZERO	 { 0, 0, 0};
const Vec3 Vec3::UP		 { 0, 1, 0};
const Vec3 Vec3::DOWN	 { 0,-1, 0};
const Vec3 Vec3::LEFT	 {-1, 0, 0};
const Vec3 Vec3::RIGHT	 { 1, 0, 0};
const Vec3 Vec3::FORWARD { 0, 0,-1};
const Vec3 Vec3::BACK    { 0, 0, 1};

bool Vec3::operator==(const Vec3& v) const {
	return
		eps_equal(x, v.x) &&
		eps_equal(y, v.y) &&
		eps_equal(z, v.z)
	;
}

bool Vec3::operator!=(const Vec3& v) const {
	return ! (*this == v);
}

Vec3 Vec3::operator+(const Vec3& v) const {
	return {
		x + v.x,
		y + v.y,
		z + v.z
	};
}

Vec3 Vec3::operator-(const Vec3& v) const {
	return {
		x - v.x,
		y - v.y,
		z - v.z
	};
}

Vec3 Vec3::operator-() const {
	return {
		-x,
		-y,
		-z
	};
}

Vec3 Vec3::operator*(float f) const {
	return {
		x * f,
		y * f,
		z * f
	};
}

Vec3 Vec3::operator*(const Vec3& v) const {
	return {
		x * v.x,
		y * v.y,
		z * v.z
	};
}

Vec3 Vec3::operator/(float f) const {
	return {
		x / f,
		y / f,
		z / f
	};
}

Vec3 Vec3::operator/(const Vec3& v) const {
	return {
		x / v.x,
		y / v.y,
		z / v.z
	};
}

Vec3 operator*(float f, const Vec3& v) {
	return v * f;
}

Vec3& Vec3::operator+=(const Vec3& v) {
	*this = *this + v;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
	*this = *this - v;
	return *this;
}

Vec3& Vec3::operator*=(float f) {
	*this = *this * f;
	return *this;
}

Vec3& Vec3::operator/=(float f) {
	*this = *this / f;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
	return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

bool Vec3::is_normalized() const {
	return eps_equal(len_squared(), 1.0);
}

float Vec3::len() const {
	return sqrt(len_squared());
}

float Vec3::len_squared() const {
	return x*x + y*y + z*z;
}

float Vec3::distance(const Vec3& v) const {
	return sqrt(distance_squared(v));
}

float Vec3::distance_squared(const Vec3& v) const {
	return (*this - v).len_squared();
}

float Vec3::angle_with(const Vec3& v) const {
	float aux = len_squared() * v.len_squared();
	return acos(dot(v) / sqrt(aux));
}

float Vec3::dot(const Vec3& v) const {
	return x*v.x + y*v.y + z*v.z;
}

Vec3 Vec3::cross(const Vec3& v) const {
	return {
		y*v.z - z*v.y,
		x*v.z - z*v.x,
		x*v.y - y*v.x
	};
}

Vec3 Vec3::lerp(const Vec3& to, float t) const {
	Vec3 delta = to - *this;
	return *this + (delta * t);
}

Vec3 Vec3::direction_to(const Vec3& v) const {
	return (v - *this).normalized();
}

Vec3 Vec3::limited_len(float max_len) const {
	if (len_squared() < max_len*max_len)
		return *this;

	return normalized() * max_len;
}

Vec3 Vec3::move_toward(const Vec3& to, float step) const {
	Vec3 delta = to - *this;
	
	if (delta.len_squared() < step*step)
		return to;

	return *this + step * delta.normalized();
}

Vec3 Vec3::normalized() const {
	if (*this == Vec3::ZERO)
		return Vec3::ZERO;

	return *this / len();
}

Vec3 Vec3::rotated(const Vec3& axis, float angle) const {
	return Quat::Qrotation(axis, angle) * (*this);
}

Vec3 Vec3::reflected(const Vec3& normal) const {
	return *this - 2 * dot(normal) * normal;
}

Vec3 Vec3::projected(const Vec3& target) const {
	return target * target.dot(*this) / target.len_squared();
}

Vec3 Vec3::slide(const Vec3& normal) const {
	return *this - dot(normal) * normal;
}

