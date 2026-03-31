// TODO ownership: Heitor

#include "Camera.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "Transform2D.hpp"
#include "Vec2.hpp"
#include "AppIO.hpp"
#include "Texture.hpp"

#include <vector>

using namespace engine;
using std::string;
using std::vector;

const std::string& Sprite::getResourceType() const {
	static const std::string RES_NAME = "Sprite";
	return RES_NAME;
}

void Sprite::load() {
	Object2D::load();
	
	loadTexture();
}

void Sprite::unload() {
	Object2D::unload();

	unloadTexture();
}

void Sprite::loadTexture() {
	if (texture) {
		texture.load_ref();
		clip = {Vec2(), texture->dimensions};
	}
}

void Sprite::unloadTexture() {
	if (texture)
		texture.unload_ref();
}

void Sprite::pre_render() {
	auto pass = Game::getRenderPass();
	if (!pass) return;

	pass->queue(this);

	Object2D::pre_render();
}

void Sprite::render() {
	// call super
	Object2D::render();

	if (!texture.get()) return;
	
	const Vec2& d = getClip().dimensions;
	Vec2 vertices[4] {
		Vec2{0.0, 0.0} - pivot, // Top Left
		Vec2{d.x, 0.0} - pivot, // Top Right
		Vec2{0.0, d.y} - pivot, // Bottom Left
		Vec2{d.x, d.y} - pivot  // Bottom Right
	};

	const auto& camera = Game::getRenderPass()->active_camera;
	const Transform2D viewTransform = camera->getInverseGlobal() * getGlobalTransform();
	const Vec2 pos = viewTransform.position + camera->feed->screen_area.dimensions/2;
	const Basis2D& basis = viewTransform.basis;

	for (auto& vertex : vertices) {
		vertex = vertex.x*basis.i + vertex.y*basis.j;
		vertex += pos;
	}

	Vec2 t_d = texture->dimensions;
	Vec2 uvs[4] {
		clip.origin / t_d, // Top Left
		(clip.origin + Vec2{clip.w, 0.0}) / t_d, // Top Right
		(clip.origin + Vec2{0.0, clip.h}) / t_d, // Bottom Left
		clip.getEnd() / t_d // Bottom Right
	};

	texture->renderQuad(vertices, uvs);
}

void Sprite::setTexture(Ref<Texture> texture) {
	this->texture = texture;
	
	if (is_loaded)
		this->texture.load_ref();
	
	if (texture.get())
		clip = {Vec2(), texture->dimensions};
}

Ref<Texture> Sprite::getTexture() {
	return texture;
}

void Sprite::setClip(const Rect& clip) {
	this->clip = clip;
}

Rect Sprite::getClip() {
	return clip;
}

void Sprite::alignCenter() {
	pivot = clip.dimensions/2;
}



void SpriteSheet::setSheet(const std::vector<Rect>& frames) {
	this->frames = frames;
}

unsigned SpriteSheet::addFrame(const Rect& frame) {
	frames.push_back(frame);
	return frames.size();
}

Rect& SpriteSheet::getFrame(unsigned index) {
	return frames[index];
}

Rect SpriteSheet::getClip() {
	return getFrame(current_frame);
}

