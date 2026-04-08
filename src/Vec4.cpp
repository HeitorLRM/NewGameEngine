// TODO ownership: Heitor

#include "Vec4.hpp"
#include "Math.hpp"
#include <ostream>

using namespace engine;

const Vec4 Vec4::ZERO	 { 0, 0, 0, 0};

bool Vec4::operator==(const Vec4& v) const {
	return
		eps_equal(x, v.x) &&
		eps_equal(y, v.y) &&
		eps_equal(z, v.z) &&
		eps_equal(w, v.w);
	;
}

bool Vec4::operator!=(const Vec4& v) const {
	return ! (*this == v);
}

Vec4 Vec4::operator+(const Vec4& v) const {
	return {
		x + v.x,
		y + v.y,
		z + v.z,
		w + v.w
	};
}

Vec4 Vec4::operator-(const Vec4& v) const {
	return {
		x - v.x,
		y - v.y,
		z - v.z,
		w - v.w
	};
}

Vec4 Vec4::operator-() const {
	return {
		-x,
		-y,
		-z,
		-w
	};
}

Vec4 Vec4::operator*(float f) const {
	return {
		x * f,
		y * f,
		z * f,
		w * f
	};
}

Vec4 Vec4::operator*(const Vec4& v) const {
	return {
		x * v.x,
		y * v.y,
		z * v.z,
		w * v.w
	};
}

Vec4 Vec4::operator/(float f) const {
	return {
		x / f,
		y / f,
		z / f,
		w / f
	};
}

Vec4 Vec4::operator/(const Vec4& v) const {
	return {
		x / v.x,
		y / v.y,
		z / v.z,
		w / v.w
	};
}

Vec4 operator*(float f, const Vec4& v) {
	return v * f;
}

Vec4& Vec4::operator+=(const Vec4& v) {
	*this = *this + v;
	return *this;
}

Vec4& Vec4::operator-=(const Vec4& v) {
	*this = *this - v;
	return *this;
}

Vec4& Vec4::operator*=(float f) {
	*this = *this * f;
	return *this;
}

Vec4& Vec4::operator/=(float f) {
	*this = *this / f;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vec4& v) {
	return os << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
}

bool Vec4::is_normalized() const {
	return eps_equal(len_squared(), 1.0);
}

float Vec4::len() const {
	return sqrt(len_squared());
}

float Vec4::len_squared() const {
	return x*x + y*y + z*z + w*w;
}

float Vec4::angle_with(const Vec4& v) const {
	float aux = len_squared() * v.len_squared();
	return acos(dot(v) / sqrt(aux));
}

float Vec4::dot(const Vec4& v) const {
	return x*v.x + y*v.y + z*v.z + w*v.z;
}

Vec4 Vec4::lerp(const Vec4& to, float t) const {
	Vec4 delta = to - *this;
	return *this + (delta * t);
}

Vec4 Vec4::normalized() const {
	if (*this == Vec4::ZERO)
		return Vec4::ZERO;

	return *this / len();
}

/* TODO: implement and use quaternions
Vec4 Vec4::rotated(const Vec3& axis, float angle) const {
}
*/

