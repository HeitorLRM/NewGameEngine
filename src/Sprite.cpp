// TODO ownership: Heitor

#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Rect.hpp"
#include "Stage.hpp"
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
	if (texture) texture->render(
		getClip(), 
		Rect(getGlobalPosition(), getClip().getDimensions())
	);

	GameObject::render();
}

void Sprite::setTexture(shared_ptr<Texture> texture) {
	this->texture = texture;
	
	if (texture)
		clip = Rect(Vec2(), texture->getDimensions());
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

