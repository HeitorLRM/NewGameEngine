#include "SDL_impl.hpp"

#ifdef IMPLEMENTATION_SDL3

#include <memory>

using namespace engine;

using std::string;
using std::shared_ptr;

TextureSDL::TextureSDL(SDLInterface* target) :
{
}

TextureSDL::~TextureSDL() {
}

bool TextureSDL::loadFromFile(const string& file) {
}

void TextureSDL::render(const Rect& clip, const Rect& dst) {
}

SDLInterface* SDLInterface::getInstance() {
}

SDLInterface::SDLInterface() :
{
}

SDLInterface::~SDLInterface() {
}

shared_ptr<Texture> SDLInterface::loadTextureFromFile(const std::string& file) {
}

bool SDLInterface::isOpen() {
}

SDL_Window* SDLInterface::getWindow() {
}

SDL_Renderer* SDLInterface::getRenderer() {
}

void SDLInterface::render() {
}

bool SDLInterface::shouldClose() {
}

void SDLInterface::init(
	const string& windowTitle,
	const Vec2& windowDimensions
) {
}

void SDLInterface::close() {
}

void SDLInterface::initSDL() {
}

void SDLInterface::closeSDL() {
}

void SDLInterface::initSDLImg() {
}

void SDLInterface::closeSDLImg() {
}

void SDLInterface::initSDLMix() {
}

void SDLInterface::closeSDLMix() {
}

void SDLInterface::initSDLFont() {
}

void SDLInterface::closeSDLFont() {
}

void SDLInterface::initWindow(
	const string& windowTitle,
	const Vec2& windowDimensions
) {
}

void SDLInterface::closeWindow() {
}

void SDLInterface::initRenderer() {
}

void SDLInterface::closeRenderer() {
}

#endif//IMPLEMENTATION_SDL3
