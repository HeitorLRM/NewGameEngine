#include "MusicPlayer.hpp"

namespace SkyCircuit {
extern bool music_enabled;
}

using namespace engine;

const std::string& MusicPlayer::getResourceType() const {
	static const std::string RES_NAME = "MusicPlayer";
	return RES_NAME;
}

void MusicPlayer::load() {
	GameObject::load();
	was_music_enabled = SkyCircuit::music_enabled;
	loadMusic();
}

void MusicPlayer::unload() {
	GameObject::unload();
	unloadMusic();
}

void MusicPlayer::update(float dt) {
	GameObject::update(dt);
	if (SkyCircuit::music_enabled != was_music_enabled) {
		was_music_enabled = SkyCircuit::music_enabled;
		if (music) {
			if (was_music_enabled) {
				music->play(-1);
			} else {
				music->stop();
			}
		}
	}
}

void MusicPlayer::loadMusic() {
	if (music) {
		music.load_ref();
		if (was_music_enabled) {
			music->play(-1);
		}
	}
}

void MusicPlayer::unloadMusic() {
	if (music) {
		music->stop();
		music.unload_ref();
	}
}

void MusicPlayer::setMusic(Ref<Music> music) {
	if (is_loaded) {
		unloadMusic();
	}

	this->music = music;

	if (is_loaded) {
		loadMusic();
	}
}

Ref<Music> MusicPlayer::getMusic() {
	return music;
}
