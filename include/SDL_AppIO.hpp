#pragma once

#include "Texture.hpp"
#include "Vec2.hpp"
#include "Ref.hpp"

#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class MIX_Mixer;

namespace engine::AppIO::SDL {

extern void initSDL();
extern void closeSDL();
extern void updateKeyboard();

extern Ref<engine::Texture> loadTextureFromFile(const std::string& file);

extern std::string window_title;
extern Vec2 window_dimensions;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern MIX_Mixer* mixer;



/*
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
	Ref<Texture> loadTextureFromFile(const std::string& file) override;

private:
	void init(
		const std::string& windowTitle,
		const Vec2& windowDimensions
	);
	void close();
	void updateKeyboard();



};
*/
}
