#pragma once

#include "Color.hpp"
#include "Rect.hpp"
#include "RenderPass.hpp"
#include "Resource.hpp"

class SDL_Texture;

namespace engine {

class CameraFeed : public Resource {
public:
	virtual const std::string& getResourceType() const override;

	void load() override;
	void unload() override;

public:
	Rect screen_area;
	Color fill_color;

private:
	SDL_Texture* output;
	friend RenderPass;
};

}
