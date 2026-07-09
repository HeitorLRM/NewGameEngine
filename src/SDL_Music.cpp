#include "SDL_Music.hpp"
#include "Ref.hpp"
#include "SDL_AppIO.hpp"

#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL_properties.h>
#include <SDL3/SDL_error.h>
#include <stdexcept>

using namespace engine;
using std::runtime_error;
using std::string;

// Music -------------------------------------------

const std::string& Music::getResourceType() const {
	static const std::string RES_NAME = "Music";
	return RES_NAME;
}

void Music::load() {
	Resource::load();
}

void Music::unload() {
	Resource::unload();
}

Ref<Music> engine::Music::fromFile(const string& filepath) {
	engine::SDL::Music* music = new engine::SDL::Music();
	music->load_path = filepath;
	return Ref<engine::Music>(music);
}

// SDL::Music --------------------------------------

SDL::Music::Music() :
	engine::Music(),
	sdl_audio(nullptr),
	sdl_track(nullptr)
{
}

void SDL::Music::load() {
	engine::Music::load();

	// Load audio (streamed/on-the-fly decoded for music, predecode = false)
	sdl_audio = MIX_LoadAudio(AppIO::SDL::mixer, load_path.c_str(), false);
	if (sdl_audio == nullptr) {
		throw runtime_error("could not load audio file '" + load_path + "'. Error: " + SDL_GetError());
	}

	// Create a track for playback on the mixer
	sdl_track = MIX_CreateTrack(AppIO::SDL::mixer);
	if (sdl_track == nullptr) {
		MIX_DestroyAudio(sdl_audio);
		sdl_audio = nullptr;
		throw runtime_error(std::string("could not create mixer track. Error: ") + SDL_GetError());
	}

	// Assign the audio to the track
	if (!MIX_SetTrackAudio(sdl_track, sdl_audio)) {
		MIX_DestroyTrack(sdl_track);
		sdl_track = nullptr;
		MIX_DestroyAudio(sdl_audio);
		sdl_audio = nullptr;
		throw runtime_error(std::string("could not assign audio to track. Error: ") + SDL_GetError());
	}
}

void SDL::Music::unload() {
	engine::Music::unload();

	if (sdl_track != nullptr) {
		MIX_DestroyTrack(sdl_track);
		sdl_track = nullptr;
	}

	if (sdl_audio != nullptr) {
		MIX_DestroyAudio(sdl_audio);
		sdl_audio = nullptr;
	}
}

void SDL::Music::play(int loops) {
	if (sdl_track != nullptr) {
		SDL_PropertiesID props = SDL_CreateProperties();
		if (props != 0) {
			SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
			MIX_PlayTrack(sdl_track, props);
			SDL_DestroyProperties(props);
		} else {
			MIX_PlayTrack(sdl_track, 0);
		}
	}
}

void SDL::Music::stop() {
	if (sdl_track != nullptr) {
		MIX_StopTrack(sdl_track, 0);
	}
}
