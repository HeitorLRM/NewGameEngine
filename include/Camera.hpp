#pragma once

#include "Game.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "Ref.hpp"
#include "RenderPass.hpp"
#include "Resource.hpp"

class SDL_Texture;

namespace engine {

class CameraFeed : public Resource {
public:
	void load() override;
	void unload() override;

public:
	Rect screen_area;

private:
	SDL_Texture* output;
	friend RenderPass;
};


class Camera : public Object2D {
public:
	void load() override;
	void unload() override;
	void update(float) override;

public:
	Ref<CameraFeed> feed = Game::window_feed;
	bool is_active = true;
};

}
