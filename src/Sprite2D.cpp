// TODO ownership: Heitor

#include "Sprite2D.hpp"

#include "Camera2D.hpp"
#include "Game.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "RenderPass.hpp"
#include "Transform2D.hpp"
#include "Vec2.hpp"
#include "AppIO.hpp"
#include "Texture.hpp"

#include <array>

using namespace engine;
using std::string;
using std::array;

const std::string& Sprite2D::getResourceType() const {
	static const std::string RES_NAME = "Sprite2D";
	return RES_NAME;
}

void Sprite2D::load() {
	Object2D::load();
	
	loadTexture();
}

void Sprite2D::unload() {
	Object2D::unload();

	unloadTexture();
}

void Sprite2D::loadTexture() {
	if (texture) {
		texture.load_ref();
	}
}

void Sprite2D::unloadTexture() {
	if (texture)
		texture.unload_ref();
}

void Sprite2D::pre_render() {
	auto pass = Game::getRenderPass();
	if (!pass || !pass->active_camera2D) return;

	pass->queue(this);

	Object2D::pre_render();
}

void Sprite2D::render() {
	// call super
	Object2D::render();

	if (!texture.get()) return;
	
	const Vec2 d = getDimensions();
	array<Vec2,4> vertices {
		Vec2{0.0, 0.0} - pivot, // Top Left
		Vec2{d.x, 0.0} - pivot, // Top Right
		Vec2{0.0, d.y} - pivot, // Bottom Left
		Vec2{d.x, d.y} - pivot  // Bottom Right
	};

	const auto camera = Game::getRenderPass()->active_camera2D;
	const Transform2D viewTransform = camera->getInverseGlobal() * getGlobalTransform();
	const Vec2 pos = viewTransform.position + camera->feed->screen_area.dimensions/2;
	const Basis2D& basis = viewTransform.basis;

	for (auto& vertex : vertices) {
		vertex = vertex.x*basis.i + vertex.y*basis.j;
		vertex += pos;
	}

	texture->renderQuad(vertices, getUVs());
}

void Sprite2D::setTexture(Ref<Texture> texture) {
	this->texture = texture;
	
	if (is_loaded)
		this->texture.load_ref();
}

Ref<Texture> Sprite2D::getTexture() {
	return texture;
}

Vec2 Sprite2D::getDimensions() const {
	return texture->dimensions / Vec2{(float)spritesheet.horizontal_count, (float)spritesheet.vertical_count};
}

void Sprite2D::alignCenter() {
	pivot = getDimensions()/2.0;
}

array<Vec2, 4> Sprite2D::getUVs() const {
	unsigned i = current_frame % spritesheet.horizontal_count;
	unsigned j = current_frame / spritesheet.vertical_count;
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

