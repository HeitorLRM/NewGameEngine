// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
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

	void setClip(const Rect& clip);
	virtual Rect getClip();

	void alignCenter();

	Vec2 pivot{0.0, 0.0};

protected:
	void loadTexture();
	void unloadTexture();

public:
	int z_index = 0;

protected:
	Rect clip;

	Ref<Texture> texture;
};

}
