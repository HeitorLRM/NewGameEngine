#pragma once

#include "Sprite3D.hpp"

#include <vector>

namespace engine {

class SpriteStack3D : public Sprite3D {
public:
	void render() override;

	std::vector<unsigned> stack;
	float separation = pixel_size;
};

}
