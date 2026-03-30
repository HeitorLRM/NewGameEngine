#include "SDL_AppIO.hpp"
#include "AppIO.hpp"
#include "KeyboardInput.hpp"
#include "SDL_keycode.h"
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
	SDL::updateKeyboard();
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

void AppIO::SDL::updateKeyboard() {
	SDL_Event event;
	KeyboardState new_state = AppIO::keyboard.getState();
	SDL_PumpEvents();
	while (
		SDL_PeepEvents(
			&event, 
			1, 
			SDL_GETEVENT, 
			SDL_EVENT_KEY_DOWN, 
			SDL_EVENT_KEY_UP)
	) {

		unsigned char key_state = event.key.down ? 1 : 0;

		#define KEYCASE(sdl_key, key) \
			case (sdl_key):\
				new_state.key = key_state;\
				break;

		switch (event.key.key) {
			KEYCASE(SDLK_A, A);
			KEYCASE(SDLK_B, B);
			KEYCASE(SDLK_C, C);
			KEYCASE(SDLK_D, D);
			KEYCASE(SDLK_E, E);
			KEYCASE(SDLK_F, F);
			KEYCASE(SDLK_G, G);
			KEYCASE(SDLK_H, H);
			KEYCASE(SDLK_I, I);
			KEYCASE(SDLK_J, J);
			KEYCASE(SDLK_K, K);
			KEYCASE(SDLK_L, L);
			KEYCASE(SDLK_M, M);
			KEYCASE(SDLK_N, N);
			KEYCASE(SDLK_O, O);
			KEYCASE(SDLK_P, P);
			KEYCASE(SDLK_Q, Q);
			KEYCASE(SDLK_R, R);
			KEYCASE(SDLK_S, S);
			KEYCASE(SDLK_T, T);
			KEYCASE(SDLK_U, U);
			KEYCASE(SDLK_V, V);
			KEYCASE(SDLK_W, W);
			KEYCASE(SDLK_X, X);
			KEYCASE(SDLK_Y, Y);
			KEYCASE(SDLK_Z, Z);
			KEYCASE(SDLK_0, _0);
			KEYCASE(SDLK_1, _1);
			KEYCASE(SDLK_2, _2);
			KEYCASE(SDLK_3, _3);
			KEYCASE(SDLK_4, _4);
			KEYCASE(SDLK_5, _5);
			KEYCASE(SDLK_6, _6);
			KEYCASE(SDLK_7, _7);
			KEYCASE(SDLK_8, _8);
			KEYCASE(SDLK_9, _9);
			KEYCASE(SDLK_UP, UP);
			KEYCASE(SDLK_DOWN, DOWN);
			KEYCASE(SDLK_LEFT, LEFT);
			KEYCASE(SDLK_RIGHT, RIGHT);
			KEYCASE(SDLK_SPACE, SPACEBAR);
			KEYCASE(SDLK_LSHIFT, SHIFT);
			KEYCASE(SDLK_LCTRL, CTRL);
			KEYCASE(SDLK_ESCAPE, ESC);
		}

		#undef KEYCASE

		SDL_PumpEvents();
	}
	
	AppIO::keyboard.update(new_state);
}

