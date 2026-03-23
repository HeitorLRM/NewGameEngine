#pragma once

#include "SDL_AppIO.hpp"
#include "Texture.hpp"

class SDL_Texture;

namespace engine::SDL {

class Texture : public engine::Texture {
public:
	Texture(SDL::AppIO* target);

	void load() override;
	void unload() override;
	void render(const Rect& clip, const Rect& dst) override;
	void renderQuad(const Vec2 (&vertices)[4], const Vec2 (&uvs)[4]) override;

private:
	SDL::AppIO* target;
	SDL_Texture* sdl_texture;
	
friend SDL::AppIO;
};

}