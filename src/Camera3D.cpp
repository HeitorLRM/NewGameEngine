#include "Camera3D.hpp"

#include "Matrix4.hpp"
#include "Object3D.hpp"
#include "CameraFeed.hpp"
#include "Game.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

#include <SDL3/SDL_render.h>
#include <cmath>
#include <string>
#include <utility>

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
	const float zz = -2.0f * near * far;

	return {
		t/a, 0, 0, 0,
		0,   t, 0, 0,
		0,   0, -zp/zm, zz/zm,
		0,   0, -1, 0
	};
}

Matrix4 Camera3D::getInverseProjectionMatrix() const {
	float a = 1.0;
	if (feed)
		a = feed->screen_area.w / feed->screen_area.h;

	const float t = 1/tan(fov/2.0);
	const float zp = far + near;
	const float zm = far - near;
	const float zz = -2.0f*near*far;

	return {
		a/t, 0, 0, 0,
		0, 1/t, 0, 0,
		0, 0, 0, -1,
		0, 0, zm/zz, -zp/zz
	};
}

std::pair<Vec3, Vec3> Camera3D::castRayFromView(const Vec2& screen_pos) {
	// Pretty sure it doesn't work
	Vec2 clip_pos = screen_pos/feed->screen_area.dimensions;
	clip_pos = {2.0f*clip_pos.x - 1.0f, 1.0f - 2.0f*clip_pos.y};
	Vec4 near_clip = {clip_pos.x, clip_pos.y, -1, 1};
	Vec4 far_clip = {clip_pos.x, clip_pos.y, 1, 1};

	Matrix4 inv_proj = getInverseProjectionMatrix();
	Matrix4 inv_view = getInverseGlobal().matrix;
	Matrix4 inv_proj_view = inv_view * inv_proj;

	Vec4 near_world = inv_proj_view * near_clip;
	Vec4 far_world = inv_proj_view * far_clip;

	Vec3 origin = near_world.xyz / near_world.w;
	Vec3 end = far_world.xyz / far_world.w;
	Vec3 direction = (end - origin).normalized();

	return {origin, direction};
}

