#pragma once

#include "Vec2.hpp"

#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class MIX_Mixer;

namespace engine::AppIO::SDL {

extern void initSDL();
extern void closeSDL();
extern void updateKeyboard();

extern const std::string window_title;
extern const Vec2 window_dimensions;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern MIX_Mixer* mixer;

}
