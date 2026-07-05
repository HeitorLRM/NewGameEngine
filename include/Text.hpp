#pragma once

#include "Color.hpp"
#include "Object2D.hpp"
#include "Vec2.hpp"

#include <string>

struct TTF_Font;
struct SDL_Texture;

namespace engine {

class Text : public Object2D {
public:
	virtual ~Text() override;

	virtual const std::string& getResourceType() const override;

	virtual void preRender() override;
	virtual void render() override;

	void loadFont(const std::string& path, float pointSize);
	void setText(const std::string& text);
	void setColor(const Color& color);

	Vec2 getDimensions() const { return dimensions; }

	Color modulation = {1,1,1,1};
	Vec2 pivot{0.5, 0.5};
	int z_index = 0;

private:
	void rebuildTexture();

	TTF_Font* font = nullptr;
	SDL_Texture* texture = nullptr;
	std::string text;
	Vec2 dimensions;
	bool dirty = false;
};

}
