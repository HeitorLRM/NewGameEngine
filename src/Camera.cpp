#include "Matrix3.hpp"
#include "Object2D.hpp"
#include "SDL_AppIO.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Resource.hpp"
#include "Transform2D.hpp"

#include <SDL3/SDL_render.h>
#include <string>

using namespace engine;

// CameraFeed --------------------------------------

const std::string& CameraFeed::getResourceType() const {
	static const std::string RES_NAME = "CameraFeed";
	return RES_NAME;
}


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

const std::string& Camera::getResourceType() const {
	static const std::string RES_NAME = "Camera";
	return RES_NAME;
}

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

void Camera::mark_global_transform_dirty() {
	is_inv_global_dirty = true;
	Object2D::mark_global_transform_dirty();
}

const Transform2D& Camera::getInverseGlobal() {
	if (!is_inv_global_dirty)
		return inv_global;
	is_inv_global_dirty = false;

	inv_global = {getGlobalTransform().matrix.inverse()};
	return inv_global;
}
