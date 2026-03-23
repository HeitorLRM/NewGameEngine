#include "SDL_Texture.hpp"
#include "Texture.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

#include <stdexcept>

using namespace engine;
using std::runtime_error;


SDL::Texture::Texture(SDL::AppIO* target) :
	engine::Texture(),
	target(target),
	sdl_texture(nullptr)
{
}

void SDL::Texture::load() {
	engine::Texture::load();

	sdl_texture = IMG_LoadTexture(
		target->getRenderer(),
		load_path.c_str()
	);

	if (sdl_texture != nullptr)
		SDL_GetTextureSize(
			sdl_texture, 
			&dimensions.x, 
			&dimensions.y
		);
}

void SDL::Texture::unload() {
	engine::Texture::unload();
	
	SDL_DestroyTexture(sdl_texture);
}

void SDL::Texture::render(const Rect& clip, const Rect& dst) {
	SDL_FRect dstRect = SDL_FRect{
		dst.x, 
		dst.y, 
		dst.w, 
		dst.h 
	};
	SDL_FRect clipRect = SDL_FRect{
		clip.x, 
		clip.y, 
		clip.w, 
		clip.h 
	};

	bool success = SDL_RenderTexture(
		target->getRenderer(), 
		sdl_texture, 
		&clipRect, 
		&dstRect
	);
	if (!success)
		throw runtime_error("could not render texture."); // TODO error system
}

void SDL::Texture::renderQuad(const Vec2 (&vertices)[4], const Vec2 (&uvs)[4]) {
	SDL_Vertex vertices_sdl[4];

	// Populate vertices
	for (unsigned i = 0; i < 4; i++) vertices_sdl[i] = {
		vertices[i].x, vertices[i].y,
		1.0, 1.0, 1.0, 1.0,
		uvs[i].x, uvs[i].y
	};
	const int indices[6] = {0, 1, 2, 2, 1, 3};

	SDL_RenderGeometry(
		target->getRenderer(), 
		sdl_texture, 
		vertices_sdl, 
		4, 
		indices, 
		6
	);
}
