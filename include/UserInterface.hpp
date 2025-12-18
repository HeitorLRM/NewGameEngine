// TODO ownership: Heitor

#pragma once

#include <memory>
namespace engine {

class Texture;

class UserInterface {
public:
	virtual void render() = 0;

	virtual bool shouldClose() = 0;

	virtual std::shared_ptr<Texture> loadTextureFromFile(const std::string& file) = 0;
};

}
