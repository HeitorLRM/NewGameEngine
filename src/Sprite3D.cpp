// TODO ownership: Heitor

#include "Basis3D.hpp"
#include "Camera3D.hpp"
#include "Sprite3D.hpp"
#include "Game.hpp"
#include "Rect.hpp"
#include "Transform3D.hpp"
#include "Vec2.hpp"
#include "AppIO.hpp"
#include "Texture.hpp"
#include "Vec3.hpp"

#include <array>

using namespace engine;
using std::string;
using std::array;

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
	if (texture)
		texture.load_ref();
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
	const Vec2 D = getDimensions() * pixel_size;
	const Vec2 P = pivot * pixel_size;
	const float L = 0.0 - P.x;
	const float R = D.x - P.x;
	const float B = 0.0 - P.y;
	const float T = D.y - P.y;
	array<Vec3,4> vertices3D {
		Vec3{L, T, 0}, // Top Left
		Vec3{R, T, 0}, // Top Right
		Vec3{L, B, 0}, // Bottom Left
		Vec3{R, B, 0}, // Bottom Right
	};

	const auto& camera = Game::getRenderPass()->active_camera3D;
	const Transform3D to_world = getGlobalTransform();
	const Transform3D to_camera = camera->getInverseGlobal();
	const Transform3D camera_global = camera->getGlobalTransform();
	const Transform3D to_clip = Transform3D{camera->getProjectionMatrix()};
	for (auto& vertex : vertices3D) {
		// World space
		if (is_billboard) vertex = 
			vertex.x*camera_global.basis.i + 
			vertex.y*camera_global.basis.j + 
			to_world.position;
		else
			vertex = to_world * vertex;

		// Camera space
		vertex = to_camera * vertex;

		// Clip space
		Vec4 v_clip = to_clip.matrix * Vec4{vertex.x, vertex.y, vertex.z, 1};
		
		// Perspective
		vertex = v_clip.xyz / v_clip.w;
		// Note: NDC space maps clip boundaries to [-1, 1] in x,y,z

		// Z-culling
		if (vertex.z < -1.0)
			return;
	} 
	// Screen space
	const Vec2 feed_offset = camera->feed->screen_area.dimensions/2;
	array<Vec2,4> vertices2D;
	for (int i=0; i<4; i++) {
		vertices2D[i].x = (1.0f + vertices3D[i].x) * feed_offset.x;
		vertices2D[i].y = (1.0f - vertices3D[i].y) * feed_offset.y;
	}

	texture->renderQuad(vertices2D, getFrameUVs(current_frame));
}

void Sprite3D::setTexture(Ref<Texture> texture) {
	this->texture = texture;

	if (is_loaded)
		this->texture.load_ref();
}

Ref<Texture> Sprite3D::getTexture() {
	return texture;
}

Vec2 Sprite3D::getDimensions() const {
	return texture->dimensions / Vec2{(float)spritesheet.horizontal_count, (float)spritesheet.vertical_count};
}

void Sprite3D::alignCenter() {
	pivot = getDimensions()/2.0;
}

array<Vec2, 4> Sprite3D::getFrameUVs(unsigned frame) const {
	unsigned i = frame % spritesheet.horizontal_count;
	unsigned j = frame / spritesheet.vertical_count;
	Vec2 size = {(float)spritesheet.horizontal_count, (float)spritesheet.vertical_count};
	Vec2 d = Vec2{1.0, 1.0} / size;
	Vec2 origin = Vec2{(float)i,(float)j} / size;
	return {
		origin, // Top Left
		origin + Vec2{d.x,0.0}, // Top Right
		origin + Vec2{0.0,d.y}, // Bottom Left
		origin + d // Bottom Right
	};
}
