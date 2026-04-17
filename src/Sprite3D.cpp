// TODO ownership: Heitor

#include "Camera3D.hpp"
#include "Camera.hpp"
#include "Sprite3D.hpp"
#include "Game.hpp"
#include "Rect.hpp"
#include "Transform3D.hpp"
#include "Vec2.hpp"
#include "AppIO.hpp"
#include "Texture.hpp"
#include "Vec3.hpp"

using namespace engine;
using std::string;

const std::string& Sprite3D::getResourceType() const {
	static const std::string RES_NAME = "Sprite3D";
	return RES_NAME;
}

void Sprite3D::load() {
	Object3D::load();

	loadTexture();
}

void Sprite3D::unload() {
	Object3D::unload();

	unloadTexture();
}

void Sprite3D::loadTexture() {
	if (texture) {
		texture.load_ref();
		clip = {Vec2(), texture->dimensions};
	}
}

void Sprite3D::unloadTexture() {
	if (texture)
		texture.unload_ref();
}

void Sprite3D::pre_render() {
	auto pass = Game::getRenderPass();
	if (!pass || !pass->active_camera3D) return;

	Transform3D view = pass->active_camera3D->getInverseGlobal()*getGlobalTransform();
	if (view.position.z > 0)
		return;

	z_index = -view.position.z;

	pass->queue(this);

	Object3D::pre_render();
}

void Sprite3D::render() {
	Object3D::render();

	if (!texture.get()) return;

	// Model space
	const Vec2 D = getClip().dimensions * pixel_size;
	const Vec2 P = pivot * pixel_size;
	const float L = 0.0 - P.x;
	const float R = D.x - P.x;
	const float B = 0.0 - P.y;
	const float T = D.y - P.y;
	Vec3 vertices3D[4] {
		{L, T, 0}, // Top Left
		{R, T, 0}, // Top Right
		{L, B, 0}, // Bottom Left
		{R, B, 0}, // Bottom Right
	};

	// World space
	const Transform3D to_world = getGlobalTransform();
	for (auto& vertex : vertices3D) {
		if (is_billboard) 
			vertex += to_world.position;
		else
			vertex = to_world * vertex;
	}

	// Camera space
	const auto& camera = Game::getRenderPass()->active_camera3D;
	const Transform3D to_camera = camera->getInverseGlobal();

	for (auto& vertex : vertices3D) {
		vertex = to_camera * vertex;
		if (
			-vertex.z < camera->near ||
			-vertex.z > camera->far
		)	return;
	}

	// Clip space
	const Transform3D to_clip = Transform3D{camera->getProjectionMatrix()};

	for (auto& vertex : vertices3D) {
		Vec4 v4 = to_clip.matrix * Vec4{vertex.x, vertex.y, vertex.z, 1};
		vertex = v4.xyz/v4.w;
	}

	// Note: screen limits map to [-1, 1] in x,y

	// Screen space
	const Vec2 feed_offset = camera->feed->screen_area.dimensions/2;
	Vec2 vertices2D[4];
	for (int i=0; i<4; i++) {
		vertices2D[i].x = (1.0f + vertices3D[i].x) * feed_offset.x;
		vertices2D[i].y = (1.0f - vertices3D[i].y) * feed_offset.y;
	}

	Vec2 t_d = texture->dimensions;
	Vec2 uvs[4] {
		clip.origin / t_d, // Top Left
		(clip.origin + Vec2{clip.w, 0.0}) / t_d, // Top Right
		(clip.origin + Vec2{0.0, clip.h}) / t_d, // Bottom Left
		clip.getEnd() / t_d // Bottom Right
	};

	texture->renderQuad(vertices2D, uvs);
}

void Sprite3D::setTexture(Ref<Texture> texture) {
	this->texture = texture;

	if (is_loaded)
		this->texture.load_ref();

	if (texture.get())
		clip = {Vec2(), texture->dimensions};
}

Ref<Texture> Sprite3D::getTexture() {
	return texture;
}

void Sprite3D::setClip(const Rect& clip) {
	this->clip = clip;
}

Rect Sprite3D::getClip() {
	return clip;
}

void Sprite3D::alignCenter() {
	pivot = clip.dimensions/2;
}

