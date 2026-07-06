// TODO: ownership: Heitor

#pragma once

#include "Vec2.hpp" // IWYU pragma: export
#include "Vec3.hpp" // IWYU pragma: export
#include "Vec4.hpp" // IWYU pragma: export
#include <cmath>
#include <cstdlib>

using std::abs;

constexpr float PI = 3.14159265359;
constexpr float EPS = 1e-9;

// Comparison with a margin of error (EPS).
constexpr bool eps_equal(const float& f0, const float& f1) {
	return std::abs( f0 - f1 ) <= EPS;
}

template<typename T>
constexpr T lerp(T a, T b, float t) {
	T delta = b - a;
	return a + t*delta;
}

template<typename T>
constexpr T damp(T from, T target, float tau, float delta_time) {
	float t = 1.0f - exp(-delta_time/tau);
	return lerp(from, target, t);
}

inline float randf() {
	return float(rand()) / RAND_MAX;
}

inline float randf(float min_val, float max_val) {
	return lerp(min_val, max_val, randf());
}
