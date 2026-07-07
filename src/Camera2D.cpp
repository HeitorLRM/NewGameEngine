#include "Matrix3.hpp"
#include "Object2D.hpp"
#include "Camera2D.hpp"
#include "Game.hpp"
#include "RenderPass.hpp"
#include "Sprite2D.hpp"
#include "Text.hpp"
#include "Transform2D.hpp"

#include <SDL3/SDL_render.h>
#include <string>

using namespace engine;

const std::string& Camera2D::getResourceType() const {
	static const std::string RES_NAME = "Camera";
	return RES_NAME;
}

void Camera2D::load() {
	Object2D::load();

	feed.load_ref();
}

void Camera2D::unload() {
	feed.unload_ref();

	Object2D::unload();
}

void Camera2D::update(float dt) {
	Object2D::update(dt);

	if (!is_active) 
		return;

	Game::registerPass(this);
}

RenderPass::QueueEntry Camera2D::makeEntry(GameObject* obj) {
	if (auto obj_sprite = dynamic_cast<Sprite2D*>(obj))
		return {(float)obj_sprite->z_index, obj_sprite};

	if (auto obj_text = dynamic_cast<Text*>(obj))
		return {(float)obj_text->z_index, obj_text};

	return {0, nullptr};
}

void Camera2D::mark_global_transform_dirty() {
	is_inv_global_dirty = true;
	Object2D::mark_global_transform_dirty();
}

const Transform2D& Camera2D::getInverseGlobal() {
	if (!is_inv_global_dirty)
		return inv_global;
	is_inv_global_dirty = false;

	inv_global = {getGlobalTransform().matrix.inverse()};
	return inv_global;
}
