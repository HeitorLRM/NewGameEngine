#include "SDL_impl.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "AppIO.hpp"
#include "Sprite.hpp"
#include "Vec2.hpp"

#include <memory>
#include <stdexcept>


using namespace engine;

using std::string;
using std::shared_ptr;
using std::runtime_error;

TextureSDL::TextureSDL(SDLInterface* target) :
	Texture(),
	target(target),
	texture(nullptr)
{
}

TextureSDL::~TextureSDL() {
	SDL_DestroyTexture(texture);
}

bool TextureSDL::loadFromFile(const string& file) {
	if (!target) return false; // TODO error codes

	texture = IMG_LoadTexture(
		target->getRenderer(),
		file.c_str()
	);
	if (texture == nullptr) return false;

	float dim_x, dim_y;
	SDL_GetTextureSize(texture, &dim_x, &dim_y);
	dimensions = Vec2(dim_x, dim_y);

	return true;
}

void TextureSDL::render(const Rect& clip, const Rect& dst) {
	SDL_FRect dstRect = SDL_FRect{
		dst.x, 
		dst.y, 
		dst.w, 
		dst.h 
	};
	SDL_FRect clipRect = SDL_FRect{
		clip.x, 
		clip.y, 
		clip.w, 
		clip.h 
	};

	bool success = SDL_RenderTexture(
		target->getRenderer(), 
		texture, 
		&clipRect, 
		&dstRect
	);
	if (!success)
		throw runtime_error("could not render texture."); // TODO error system
}

// SDLInterface ---------------------------------------------------------------------

unsigned SDLInterface::instances = 0;

SDLInterface::SDLInterface(const string& windowTitle, const Vec2& windowDimensions) :
	AppIO(),
	window(nullptr),
	renderer(nullptr),
	mixer(nullptr)
{
	if(instances <= 0)
		initSDL();

	instances++;

	init(windowTitle, windowDimensions);
}

SDLInterface::~SDLInterface() {
	close();

	instances--;

	if (instances <= 0)
		closeSDL();
}

void SDLInterface::initSDL() {
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

void SDLInterface::closeSDL() {
	// Close ttf
	TTF_Quit();

	// Close mixer
	MIX_Quit();

	// Close SDL
	SDL_Quit();
}


bool SDLInterface::shouldClose() {
	SDL_PumpEvents();
	return SDL_PeepEvents(
		NULL, 
		0, 
		SDL_PEEKEVENT, 
		SDL_EVENT_QUIT, 
		SDL_EVENT_QUIT
	) > 0;
}

void SDLInterface::render() {
	if (renderer)
		SDL_RenderPresent(renderer);
}

SDL_Window* SDLInterface::getWindow() {
	return window;
}

SDL_Renderer* SDLInterface::getRenderer() {
	return renderer;
}

shared_ptr<Texture> SDLInterface::loadTextureFromFile(const std::string& file) {
	Texture* texture = new TextureSDL(this);
	texture->loadFromFile(file);
	return shared_ptr<Texture>(texture);
}

void SDLInterface::init(
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

void SDLInterface::close() {
	// Close window
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	// Close mixer
	MIX_DestroyMixer(mixer);
	mixer = nullptr;
}