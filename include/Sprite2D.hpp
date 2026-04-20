// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"
#include "Object2D.hpp"
#include "Texture.hpp"
#include "Vec2.hpp"

namespace engine {

class Sprite2D : public Object2D {
public:
	virtual const std::string& getResourceType() const override;

	virtual void load() override;
	virtual void unload() override;
	virtual void pre_render() override;
	virtual void render() override;
	
	void setTexture(Ref<Texture> texture);
	Ref<Texture> getTexture();
	Vec2 getDimensions() const;

	void alignCenter();

	Vec2 pivot{0.0, 0.0};

protected:
	std::array<Vec2, 4> getFrameUVs(unsigned frame) const;

	void loadTexture();
	void unloadTexture();

public:
	struct {
		unsigned horizontal_count = 1;
		unsigned vertical_count = 1;
	} spritesheet;

	unsigned current_frame = 0;
	int z_index = 0;

protected:
	Ref<Texture> texture;
};

}
