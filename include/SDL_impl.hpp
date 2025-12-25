// TODO ownership Heitor

#pragma once

#define IMPLEMENTATION_SDL2

#include "Sprite.hpp"
#include "UserInterface.hpp"
#include "Vec2.hpp"
#include <memory>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
namespace engine {

class SDLInterface;

class TextureSDL : public Texture {
public:
	TextureSDL(SDLInterface* target);
	~TextureSDL();

	bool loadFromFile(const std::string&) override;
	void render(const Rect& clip, const Rect& dst) override;

private:
	SDLInterface* target;
	SDL_Texture* texture;
}; // SDL wrapper

class SDLInterface final : public UserInterface {
public:
	// Singleton
	static SDLInterface* getInstance();

private:
	SDLInterface();
	SDLInterface(const SDLInterface&) = default;
	SDLInterface& operator=(SDLInterface const&);

public:
	~SDLInterface();

	void render();
	void init(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	void close();

	std::shared_ptr<Texture> loadTextureFromFile(const std::string& file);

	bool shouldClose();
	bool isOpen();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

private:
	void initSDL();
	void closeSDL();

	void initSDLImg();
	void closeSDLImg();

	void initSDLMix();
	void closeSDLMix();

	void initSDLFont();
	void closeSDLFont();

	void initWindow(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	void closeWindow();

	void initRenderer();
	void closeRenderer();

private:
	bool open;
	SDL_Window* window;
	SDL_Renderer* renderer;

};




}


