#include "Texture.hpp"
#include "Vec2.hpp"

#include <memory>
#include <string>

using namespace engine;
using std::shared_ptr;
using std::weak_ptr;
using std::string;

Vec2 Texture::getDimensions() {
	return dimensions;
}

shared_ptr<Texture> Texture::loadFromFile(const string& filename, weak_ptr<AppIO> interface) {
	auto i = interface.lock();
	if (!i) return nullptr;
	return i->loadTextureFromFile(filename);
}
