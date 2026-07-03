#pragma once

#include "Color.hpp"
#include "Rect.hpp"
#include "Resource.hpp"

class SDL_Texture;

namespace engine {

class CameraFeed : public Resource {
public:
	virtual const std::string& getResourceType() const override;

	void load() override;
	void unload() override;
	void clear();

public:
	Rect screen_area;
	Color fill_color;
	SDL_Texture* output;
};

}
