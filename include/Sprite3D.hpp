// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"
#include "Object3D.hpp"
#include "Texture.hpp"
#include "Vec2.hpp"
#include <array>

namespace engine {

class Sprite3D : public Object3D {
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
	virtual std::array<Vec2, 4> getUVs() const;

	void loadTexture();
	void unloadTexture();

public:
	float pixel_size = 1.0/64.0;
	bool is_billboard = false;

	struct {
		unsigned horizontal_count = 1;
		unsigned vertical_count = 1;
	} spritesheet;

	unsigned current_frame = 0;

	float z_index;

protected:
	Ref<Texture> texture;
};


}
