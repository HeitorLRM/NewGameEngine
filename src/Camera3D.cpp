#include "Matrix4.hpp"
#include "Object3D.hpp"
#include "Camera3D.hpp"
#include "Camera.hpp"
#include "Game.hpp"

#include <SDL3/SDL_render.h>
#include <cmath>
#include <string>

using namespace engine;

const std::string& Camera3D::getResourceType() const {
	static const std::string RES_NAME = "Camera3D";
	return RES_NAME;
}

void Camera3D::load() {
	Object3D::load();

	feed.load_ref();
}

void Camera3D::unload() {
	feed.unload_ref();

	Object3D::unload();
}

void Camera3D::update(float dt) {
	Object3D::update(dt);

	if (!is_active) 
		return;

	Game::registerPass(this);
}

void Camera3D::mark_global_transform_dirty() {
	is_inv_global_dirty = true;
	Object3D::mark_global_transform_dirty();
}

const Transform3D& Camera3D::getInverseGlobal() {
	if (!is_inv_global_dirty)
		return inv_global;
	is_inv_global_dirty = false;

	inv_global = {getGlobalTransform().matrix.t_inverse()};
	return inv_global;
}

Matrix4 Camera3D::getProjectionMatrix() const  {
	float a = 1.0;
	if (feed)
		a = feed->screen_area.w / feed->screen_area.h;

	const float t = 1.0/tan(fov/2.0);
	const float zp = far + near;
	const float zm = far - near;

	return {
		t/a, 0, 0, 0,
		0,   t, 0, 0,
		0,   0, -zp/zm, -(2.0f*far*near)/zm,
		0,   0, -1, 0
	};
}
