#include "SDL_AppIO.hpp"
#include "AppIO.hpp"
#include "KeyboardInput.hpp"
#include "MouseInput.hpp"
#include "Vec2.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <stdexcept>

using std::runtime_error;
using std::string;
using namespace engine;


// AppIO -------------------------------------------------------------

KeyboardInput AppIO::keyboard;
MouseInput AppIO::mouse;

bool AppIO::shouldClose() {
	SDL_PumpEvents();
	return SDL_PeepEvents(
		NULL, 
		0, 
		SDL_PEEKEVENT, 
		SDL_EVENT_QUIT, 
		SDL_EVENT_QUIT
	) > 0;
}

void AppIO::init() {
	SDL::initSDL();

	// Initialize mixer
	SDL::mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!SDL::mixer)
		throw runtime_error(SDL_GetError());

	// Initialize window
	SDL_CreateWindowAndRenderer(
		SDL::window_title.c_str(), 
		SDL::window_dimensions.x, 
		SDL::window_dimensions.y, 
		0, 
		&SDL::window, 
		&SDL::renderer
	);

	SDL_SetRenderVSync(SDL::renderer, 1); // TODO add frame cap option
}

void AppIO::close() {
	// Close window
	SDL_DestroyRenderer(SDL::renderer);
	SDL::renderer = nullptr;
	SDL_DestroyWindow(SDL::window);
	SDL::window = nullptr;

	// Close mixer
	MIX_DestroyMixer(SDL::mixer);
	SDL::mixer = nullptr;
}

void AppIO::update() {
	keyboard.update();
	mouse.update();
}

void AppIO::render() {
	if (SDL::renderer)
		SDL_RenderPresent(SDL::renderer);
}

// AppIO::SDL -------------------------------------------------------------

SDL_Window* AppIO::SDL::window = nullptr;
SDL_Renderer* AppIO::SDL::renderer = nullptr;
MIX_Mixer* AppIO::SDL::mixer = nullptr;


void AppIO::SDL::initSDL() {
	bool initialized;
	// Initialize SDL
	initialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (!initialized)
		throw runtime_error(SDL_GetError());

	// Initialize mixer
	initialized = MIX_Init();
	if (!initialized)
	    throw runtime_error(SDL_GetError());

	// Initialize ttf
	initialized = TTF_Init();
	if (!initialized)
		throw runtime_error(SDL_GetError());
}

void AppIO::SDL::closeSDL() {
	// Close ttf
	TTF_Quit();

	// Close mixer
	MIX_Quit();

	// Close SDL
	SDL_Quit();
}

