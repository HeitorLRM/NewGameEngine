#include "CameraFeed.hpp"
#include "SDL_AppIO.hpp"
#include "SDL_render.h"

using namespace engine;

const std::string& CameraFeed::getResourceType() const {
	static const std::string RES_NAME = "CameraFeed";
	return RES_NAME;
}


void CameraFeed::load() {
	Resource::load();

	output = SDL_CreateTexture(
		AppIO::SDL::renderer, 
		SDL_PIXELFORMAT_RGBA8888, 
		SDL_TEXTUREACCESS_TARGET, 
		screen_area.w, 
		screen_area.h
	);
}

void CameraFeed::unload() {
	SDL_DestroyTexture(output);

	Resource::unload();
}
