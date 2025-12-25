// TODO ownership: Heitor

#include "SDL_impl.hpp"

#ifdef IMPLEMENTATION_SDL2

#include "SDL_render.h"
#include "Sprite.hpp"
#include "UserInterface.hpp"

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
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
		file.c_str());

	if (texture == nullptr) return false;

	int dim_x, dim_y; // TODO vec2i
	SDL_QueryTexture(
		texture, 
		nullptr, 
		nullptr, 
		&dim_x, 
		&dim_y
	);

	dimensions = Vec2(dim_x, dim_y);

	return true;
}

void TextureSDL::render(const Rect& clip, const Rect& dst) {
	SDL_Rect dstRect = SDL_Rect{
		(int)dst.x, 
		(int)dst.y, 
		(int)dst.w, 
		(int)dst.h 
	};
	SDL_Rect clipRect = SDL_Rect{
		(int)clip.x, 
		(int)clip.y, 
		(int)clip.w, 
		(int)clip.h 
	};

	if (
		SDL_RenderCopy(
			target->getRenderer(), 
			texture, 
			&clipRect, 
			&dstRect
		)
	)
		throw runtime_error("could not render texture."); // TODO error system

}

SDLInterface* SDLInterface::getInstance() {
	static shared_ptr<SDLInterface> instance(nullptr);
	if (!instance) instance.reset(new SDLInterface());
	return instance.get();
}

SDLInterface::SDLInterface() :
	UserInterface(),
	open(false),
	window(nullptr),
	renderer(nullptr)
{
}

SDLInterface::~SDLInterface() {
	close();
}

shared_ptr<Texture> SDLInterface::loadTextureFromFile(const std::string& file) {
	Texture* texture = new TextureSDL(this);
	texture->loadFromFile(file);
	return shared_ptr<Texture>(texture);
}

bool SDLInterface::isOpen() {
	return open;
}

SDL_Window* SDLInterface::getWindow() {
	return window;
}

SDL_Renderer* SDLInterface::getRenderer() {
	return renderer;
}

void SDLInterface::render() {
	if (renderer)
		SDL_RenderPresent(renderer);
}

bool SDLInterface::shouldClose() {
	return SDL_QuitRequested();
}

void SDLInterface::init(
	const string& windowTitle,
	const Vec2& windowDimensions
) {
	if (open) return;
	open = true;

	initSDL();
	initSDLImg();
	initSDLMix();
	initSDLFont();
	initWindow(windowTitle, windowDimensions);
	initRenderer();
}

void SDLInterface::close() {
	if (!open) return;
	open = false;

	closeRenderer();
	closeWindow();
	closeSDLFont();
	closeSDLMix();
	closeSDLImg();
	closeSDL();
}

void SDLInterface::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
		throw SDL_GetError();	
}

void SDLInterface::closeSDL() {
	SDL_Quit();
}

void SDLInterface::initSDLImg() {
	int img_initialized;
	img_initialized = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	if ((img_initialized & IMG_INIT_JPG) == 0)
		throw runtime_error("Could not initialize JPG loader.");
	if ((img_initialized & IMG_INIT_PNG) == 0)
		throw runtime_error("Could not initialize PNG loader.");
	if ((img_initialized & IMG_INIT_TIF) == 0)
		throw runtime_error("Could not initialize TIF loader.");
}

void SDLInterface::closeSDLImg() {
	IMG_Quit();
}

void SDLInterface::initSDLMix() {
	int mix_initialized;
	mix_initialized = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	if ((mix_initialized & MIX_INIT_MP3) == 0)
		throw runtime_error("Could not initialize MP3 decoder.");
	if ((mix_initialized & MIX_INIT_OGG) == 0)
		throw runtime_error("Could not initialize OGG decoder.");

	if (Mix_OpenAudio(
		MIX_DEFAULT_FREQUENCY, 
		MIX_DEFAULT_FORMAT, 
		MIX_DEFAULT_CHANNELS, 
		1024))
		throw runtime_error("Could not open the audio device for playback.");

	Mix_AllocateChannels(32);	
}

void SDLInterface::closeSDLMix() {
	Mix_CloseAudio();
	Mix_Quit();
}

void SDLInterface::initSDLFont() {
	if (TTF_Init())
		throw runtime_error("Could initialize the font library.");	
}

void SDLInterface::closeSDLFont() {
	TTF_Quit();
}

void SDLInterface::initWindow(
	const string& windowTitle,
	const Vec2& windowDimensions
) {
	window = SDL_CreateWindow(
		windowTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowDimensions.x, 
		windowDimensions.y,
		0);
	if (window == nullptr)
		throw runtime_error("Could not create window.");
}

void SDLInterface::closeWindow() {
	SDL_DestroyWindow(window);
}

void SDLInterface::initRenderer() {
	renderer = SDL_CreateRenderer(
		window, 
		-1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		throw runtime_error("Could not create renderer.");
}

void SDLInterface::closeRenderer() {
	SDL_DestroyRenderer(renderer);
}

#endif//IMPLEMENTATION_SDL2
