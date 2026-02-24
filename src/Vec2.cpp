// TODO ownership: Heitor

#include "Vec2.hpp"
#include "Math.hpp"
#include <ostream>

using namespace engine;

const Vec2 Vec2::ZERO	( 0, 0);
const Vec2 Vec2::UP		( 0,-1);
const Vec2 Vec2::DOWN	( 0, 1);
const Vec2 Vec2::LEFT	(-1, 0);
const Vec2 Vec2::RIGHT	( 1, 0);

Vec2::Vec2(float x, float y) :
	x(x),
	y(y)
{
}

Vec2::Vec2() :
	Vec2(Vec2::ZERO)
{
}

bool Vec2::operator==(const Vec2& v) const {
	return
		eps_equal(x, v.x) &&
		eps_equal(y, v.y)
	;
}

bool Vec2::operator!=(const Vec2& v) const {
	return ! (*this == v);
}

Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(
		x + v.x,
		y + v.y
	);
}

Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(
		x - v.x,
		y - v.y
	);
}

Vec2 Vec2::operator-() const {
	return Vec2(
		-x,
		-y
	);
}

Vec2 Vec2::operator*(float f) const {
	return Vec2(
		x * f,
		y * f
	);
}

Vec2 Vec2::operator*(const Vec2& v) const {
	return Vec2(
		x * v.x,
		y * v.y
	);
}

Vec2 Vec2::operator/(float f) const {
	return Vec2(
		x / f,
		y / f
	);
}

Vec2 Vec2::operator/(const Vec2& v) const {
	return Vec2(
		x / v.x,
		y / v.y
	);
}

Vec2 operator*(float f, const Vec2& v) {
	return v * f;
}

Vec2& Vec2::operator+=(const Vec2& v) {
	*this = *this + v;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
	*this = *this - v;
	return *this;
}

Vec2& Vec2::operator*=(float f) {
	*this = *this * f;
	return *this;
}

Vec2& Vec2::operator/=(float f) {
	*this = *this / f;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
	return os << '(' << v.x << ", " << v.y << ')';
}

bool Vec2::is_normalized() const {
	return eps_equal(len_squared(), 1.0);
}

float Vec2::len() const {
	return sqrt(len_squared());
}

float Vec2::len_squared() const {
	return x*x + y*y;
}

float Vec2::distance(const Vec2& v) const {
	return sqrt(distance_squared(v));
}

float Vec2::distance_squared(const Vec2& v) const {
	return (*this - v).len_squared();
}

float Vec2::angle() const {
	return std::atan2(y, x);
}

float Vec2::angle_with(const Vec2& v) const {
	return std::atan2(
		cross(v),
		dot(v)
	);
}

float Vec2::dot(const Vec2& v) const {
	return x*v.x + y*v.y;
}

float Vec2::cross(const Vec2& v) const {
	return x*v.y - y*v.x;
}

Vec2 Vec2::lerp(const Vec2& to, float t) const {
	Vec2 delta = to - *this;
	return *this + (delta * t);
}

Vec2 Vec2::direction_to(const Vec2& v) const {
	return (v - *this).normalized();
}

Vec2 Vec2::limited_len(float max_len) const {
	if (len_squared() < max_len*max_len)
		return *this;

	return normalized() * max_len;
}

Vec2 Vec2::move_toward(const Vec2& to, float step) const {
	Vec2 delta = to - *this;
	
	if (delta.len_squared() < step*step)
		return to;

	return *this + step * delta.normalized();
}

Vec2 Vec2::normalized() const {
	if (*this == Vec2::ZERO)
		return Vec2::ZERO;

	return *this / len();
}

Vec2 Vec2::orthogonal() const {
	return Vec2(y, -x);
}

Vec2 Vec2::rotated(float angle) const {
	float s = sin(angle);
	float c = cos(angle);

	return Vec2(
		x*c - y*s,
		x*s + y*c
	);
}

Vec2 Vec2::reflected(const Vec2& normal) const {
	return *this - 2 * dot(normal) * normal;
}

Vec2 Vec2::projected(const Vec2& target) const {
	return target * target.dot(*this) / target.len_squared();
}

Vec2 Vec2::slide(const Vec2& normal) const {
	return *this - dot(normal) * normal;
}

