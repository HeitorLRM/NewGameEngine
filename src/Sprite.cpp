// TODO ownership: Heitor

#include "Sprite.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include "AppIO.hpp"
#include <memory>
#include <vector>

using namespace engine;
using std::shared_ptr;
using std::weak_ptr;
using std::string;
using std::vector;


// Texture----------------------------------------
Vec2 Texture::getDimensions() {
	return dimensions;
}

shared_ptr<Texture> Texture::loadFromFile(const string& filename, weak_ptr<AppIO> interface) {
	auto i = interface.lock();
	if (!i) return nullptr;
	return i->loadTextureFromFile(filename);
}

// Sprite ----------------------------------------
void Sprite::render() {
	// call super
	Object2D::render();

	if (!texture) return;
	
	const Vec2& d = getClip().dimensions;
	Vec2 vertices[4] {
		Vec2{0.0, 0.0} - pivot, // Top Left
		Vec2{d.x, 0.0} - pivot, // Top Right
		Vec2{0.0, d.y} - pivot, // Bottom Left
		Vec2{d.x, d.y} - pivot  // Bottom Right
	};

	const Transform2D& globalTransform = getGlobalTransform();
	const Vec2& pos = globalTransform.position;
	const Basis2D& basis = globalTransform.basis;

	for (auto& vertex : vertices) {
		vertex = vertex.x*basis.i + vertex.y*basis.j;
		vertex += pos;
	}

	Vec2 t_d = texture->getDimensions();
	Vec2 uvs[4] {
		clip.origin / t_d, // Top Left
		(clip.origin + Vec2{clip.w, 0.0}) / t_d, // Top Right
		(clip.origin + Vec2{0.0, clip.h}) / t_d, // Bottom Left
		clip.getEnd() / t_d // Bottom Right
	};

	texture->renderQuad(vertices, uvs);
}

void Sprite::setTexture(shared_ptr<Texture> texture) {
	this->texture = texture;
	
	if (texture)
		clip = {Vec2(), texture->getDimensions()};
}

shared_ptr<Texture> Sprite::getTexture() {
	return texture;
}

void Sprite::setClip(const Rect& clip) {
	this->clip = clip;
}

Rect Sprite::getClip() {
	return clip;
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

void SpriteSheet::setCurrentFrame(unsigned index) {
	this->current_frame = index;
}

unsigned SpriteSheet::getCurrentFrame() {
	return current_frame;
}

Rect SpriteSheet::getClip() {
	return getFrame(getCurrentFrame());
}

