// TODO: ownership: Heitor

#pragma once

#include <cmath>

constexpr float PI = 3.14159265359;
constexpr float EPS = 1e-9;

// Comparison with a margin of error (EPS).
constexpr bool eps_equal(const float& f0, const float& f1) {
	return std::abs( f0 - f1 ) <= EPS;
}
