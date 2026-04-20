#pragma once

#include "SDL_AppIO.hpp"
#include "Texture.hpp"

class SDL_Texture;

namespace engine::SDL {

class Texture : public engine::Texture {
public:
	Texture();

	void load() override;
	void unload() override;
	void render(const Rect& clip, const Rect& dst) override;
	void renderQuad(const std::array<Vec2,4>& vertices, const std::array<Vec2,4>& uvs) override;

private:
	SDL_Texture* sdl_texture;
	friend engine::Texture;
};

}