#include "Object2D.hpp"
#include "SDL_AppIO.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Resource.hpp"

#include <SDL3/SDL_render.h>

using namespace engine;

// CameraFeed --------------------------------------

void CameraFeed::load() {
	Resource::load();

	output = SDL_CreateTexture(
		AppIO::SDL::renderer, 
		SDL_PIXELFORMAT_RGBA8888, 
		SDL_TEXTUREACCESS_TARGET, 
		screen_area.w, 
		screen_area.h
	);
}

void CameraFeed::unload() {
	SDL_DestroyTexture(output);

	Resource::unload();
}

// Camera ------------------------------------------

void Camera::load() {
	Object2D::load();

	feed.load_ref();
}

void Camera::unload() {
	feed.unload_ref();

	Object2D::unload();
}

void Camera::update(float dt) {
	Object2D::update(dt);

	if (!is_active) 
		return;

	Game::registerPass(this);
}

