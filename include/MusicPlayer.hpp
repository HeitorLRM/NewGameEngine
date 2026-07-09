#pragma once

#include "GameObject.hpp"
#include "Music.hpp"

namespace engine {

class MusicPlayer : public GameObject {
public:
	virtual const std::string& getResourceType() const override;

	virtual void load() override;
	virtual void unload() override;
	virtual void update(float dt) override;

	void setMusic(Ref<Music> music);
	Ref<Music> getMusic();

private:
	void loadMusic();
	void unloadMusic();

private:
	Ref<Music> music;
	bool was_music_enabled = false;
};

}
