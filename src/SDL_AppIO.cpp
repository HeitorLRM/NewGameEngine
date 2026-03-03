#include "SDL_AppIO.hpp"
#include "SDL_Texture.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <memory>
#include <string>
#include <stdexcept>

using std::runtime_error;
using std::string;
using std::shared_ptr;
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

shared_ptr<engine::Texture> SDL::AppIO::loadTextureFromFile(const std::string& file) {
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
	

	return shared_ptr<Texture>(texture);
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