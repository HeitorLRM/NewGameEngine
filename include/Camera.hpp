#pragma once

#include "Game.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "Ref.hpp"
#include "RenderPass.hpp"
#include "Resource.hpp"
#include "Transform2D.hpp"

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

	const Transform2D& getInverseGlobal();

public:
	Ref<CameraFeed> feed = Game::window_feed;
	bool is_active = true;

private:
	void mark_global_transform_dirty() override;

	Transform2D inv_global;
	bool is_inv_global_dirty = true;
};

}
