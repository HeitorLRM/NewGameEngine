// TODO ownership: Heitor

#pragma once

#include "KeyboardInput.hpp"
#include "Ref.hpp"

#include <string>
namespace engine {

class Texture;

class AppIO {
public:
	virtual ~AppIO() = default;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool shouldClose() = 0;

	const KeyboardInput& getKeyboard() const {return keyboard;};

	virtual Ref<Texture> loadTextureFromFile(const std::string& file) = 0;

protected:
	
	KeyboardInput keyboard;
};

}
