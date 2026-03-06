#pragma once

#include "AppIO.hpp"
#include "Vec2.hpp"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class MIX_Mixer;

namespace engine::SDL {

class AppIO final : public engine::AppIO {
// Static
private:
	static void initSDL();
	static void closeSDL();
	static unsigned instances;

// Instance
public:	
	AppIO(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	~AppIO();

	bool shouldClose() override;
	void update() override;
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
	void updateKeyboard();

	SDL_Window* window;
	SDL_Renderer* renderer;
	MIX_Mixer* mixer;


};

}
