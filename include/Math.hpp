// TODO: ownership: Heitor

#pragma once

#include <cmath>

using std::abs;

constexpr float PI = 3.14159265359;
constexpr float EPS = 1e-9;

// Comparison with a margin of error (EPS).
constexpr bool eps_equal(const float& f0, const float& f1) {
	return std::abs( f0 - f1 ) <= EPS;
}

constexpr float lerp(float a, float b, float t) {
	float delta = b - a;
	return a + t*delta;
}

constexpr float damp(float from, float target, float tau, float delta_time) {
	float t = 1.0f - exp(-delta_time/tau);
	return lerp(from, target, t);
}

