#pragma once

#include "Vec2.hpp"

#include <SDL3/SDL_gamepad.h>
#include <string>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class MIX_Mixer;

namespace engine::AppIO::SDL {

extern void initSDL();
extern void closeSDL();

extern const std::string window_title;
extern const Vec2 window_dimensions;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern MIX_Mixer* mixer;
extern SDL_Gamepad* sdl_gamepad;

}
