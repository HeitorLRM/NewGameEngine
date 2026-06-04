#pragma once

#include "Sprite3D.hpp"

#include <vector>
#include <filesystem>

namespace engine {

class SpriteStack3D : public Sprite3D {
public:
	void render() override;
	void loadFromFile(std::filesystem::path path);

	std::vector<unsigned> stack;
	float separation = pixel_size;
};

}
