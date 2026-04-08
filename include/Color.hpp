#pragma once

#include "Vec4.hpp"
namespace engine {

class Color {
public:
	union {
		struct {
			float r = 0.0;
			float g = 0.0;
			float b = 0.0;
			float a = 1.0;
		};
		struct {
			Vec4 xyzw;
		};
	};
};

}

