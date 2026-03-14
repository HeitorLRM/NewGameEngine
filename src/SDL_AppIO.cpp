#include "SDL_AppIO.hpp"
#include "KeyboardInput.hpp"
#include "SDL_Texture.hpp"
#include "SDL_keycode.h"
#include "Texture.hpp"

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

unsigned SDL::AppIO::instances = 0;

SDL::AppIO::AppIO(const string& windowTitle, const Vec2& windowDimensions) :
	engine::AppIO(),
	window(nullptr),
	renderer(nullptr),
	mixer(nullptr)
{
	if(instances <= 0)
		initSDL();

	instances++;

	init(windowTitle, windowDimensions);
}

SDL::AppIO::~AppIO() {
	close();

	instances--;

	if (instances <= 0)
		closeSDL();
}

void SDL::AppIO::initSDL() {
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

void SDL::AppIO::closeSDL() {
	// Close ttf
	TTF_Quit();

	// Close mixer
	MIX_Quit();

	// Close SDL
	SDL_Quit();
}


bool SDL::AppIO::shouldClose() {
	SDL_PumpEvents();
	return SDL_PeepEvents(
		NULL, 
		0, 
		SDL_PEEKEVENT, 
		SDL_EVENT_QUIT, 
		SDL_EVENT_QUIT
	) > 0;
}



void SDL::AppIO::updateKeyboard() {
	SDL_Event event;
	KeyboardState new_state = keyboard.getState();
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
	
	keyboard.update(new_state);
}

void SDL::AppIO::update() {
	updateKeyboard();
}

void SDL::AppIO::render() {
	if (renderer)
		SDL_RenderPresent(renderer);
}

SDL_Window* SDL::AppIO::getWindow() {
	return window;
}

SDL_Renderer* SDL::AppIO::getRenderer() {
	return renderer;
}

Ref<engine::Texture> SDL::AppIO::loadTextureFromFile(const std::string& file) {
	SDL::Texture* texture = new SDL::Texture(this);

	texture->sdl_texture = IMG_LoadTexture(
		getRenderer(),
		file.c_str()
	);

	if (texture->sdl_texture != nullptr)
		SDL_GetTextureSize(
			texture->sdl_texture, 
			&texture->dimensions.x, 
			&texture->dimensions.y
		);
	

	return Ref<engine::Texture>(texture);
}

void SDL::AppIO::init(
	const string& windowTitle,
	const Vec2& windowDimensions
) {
	// Initialize mixer
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!mixer)
		throw runtime_error(SDL_GetError());

	// Initialize window
	SDL_CreateWindowAndRenderer(
		windowTitle.c_str(), 
		windowDimensions.x, 
		windowDimensions.y, 
		0, 
		&window, 
		&renderer
	);
	SDL_SetRenderVSync(renderer, 1); // TODO add frame cap option
}

void SDL::AppIO::close() {
	// Close window
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	// Close mixer
	MIX_DestroyMixer(mixer);
	mixer = nullptr;
}
