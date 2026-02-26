// TODO ownership Heitor

#pragma once

#include "Sprite.hpp"
#include "AppIO.hpp"
#include "Vec2.hpp"

#include <memory>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class MIX_Mixer;
namespace engine {

class SDLInterface;

class TextureSDL : public Texture {
public:
	TextureSDL(SDLInterface* target);
	~TextureSDL();

	void render(const Rect& clip, const Rect& dst) override;

private:
	SDLInterface* target;
	SDL_Texture* sdl_texture;
	
friend SDLInterface;
}; // SDL wrapper

class SDLInterface final : public AppIO {
// Static
private:
	static void initSDL();
	static void closeSDL();
	static unsigned instances;

// Instance
public:	
	SDLInterface(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	~SDLInterface();

	bool shouldClose() override;
	void render() override;
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	std::shared_ptr<Texture> loadTextureFromFile(const std::string& file) override;

private:
	void init(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	void close();

	SDL_Window* window;
	SDL_Renderer* renderer;
	MIX_Mixer* mixer;


};




}


