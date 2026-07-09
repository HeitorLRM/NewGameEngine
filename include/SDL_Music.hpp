#pragma once

#include "Music.hpp"

struct MIX_Audio;
struct MIX_Track;

namespace engine::SDL {

class Music : public engine::Music {
public:
	Music();

	void load() override;
	void unload() override;
	void play(int loops = -1) override;
	void stop() override;

private:
	MIX_Audio* sdl_audio;
	MIX_Track* sdl_track;
	friend engine::Music;
};

}
