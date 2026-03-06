// TODO ownership: Heitor

#pragma once

#include "KeyboardInput.hpp"
#include <memory>
namespace engine {

class Texture;

class AppIO {
public:
	virtual ~AppIO() = default;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool shouldClose() = 0;

	const KeyboardInput& getKeyboard() const {return keyboard;};

	virtual std::shared_ptr<Texture> loadTextureFromFile(const std::string& file) = 0;

protected:
	
	KeyboardInput keyboard;
};

}
