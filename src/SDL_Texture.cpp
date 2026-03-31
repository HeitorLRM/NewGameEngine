#include "SDL_Texture.hpp"
#include "Ref.hpp"
#include "SDL_AppIO.hpp"
#include "Texture.hpp"
#include "Vec2.hpp"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

#include <stdexcept>

using namespace engine;
using std::runtime_error;
using std::string;

// Texture -----------------------------------------

const std::string& Texture::getResourceType() const {
	static const std::string RES_NAME = "Texture";
	return RES_NAME;
}

void Texture::load() {
	Resource::load();
}

void Texture::unload() {
	Resource::unload();
}

Ref<Texture> engine::Texture::fromFile(const string& filepath) {
	// TODO: figure out dimensions without loading
	engine::SDL::Texture* texture = new engine::SDL::Texture();
	texture->load_path = filepath;
	return Ref<engine::Texture>(texture);
}

// SDL::Texture -----------------------------------------

SDL::Texture::Texture() :
	engine::Texture(),
	sdl_texture(nullptr)
{
}

void SDL::Texture::load() {
	engine::Texture::load();

	sdl_texture = IMG_LoadTexture(
		AppIO::SDL::renderer,
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
		AppIO::SDL::renderer, 
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
	for (unsigned i = 0; i < 4; i++) {
		vertices_sdl[i] = {
			vertices[i].x, vertices[i].y,
			1.0, 1.0, 1.0, 1.0,
			uvs[i].x, uvs[i].y
		};
	}
	const int indices[6] = {0, 1, 2, 2, 1, 3};

	SDL_RenderGeometry(
		AppIO::SDL::renderer, 
		sdl_texture, 
		vertices_sdl, 
		4, 
		indices, 
		6
	);
}
