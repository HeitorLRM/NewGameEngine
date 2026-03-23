// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "Texture.hpp"
#include "Vec2.hpp"

#include <string>
#include <vector>

namespace engine {

class Sprite : public Object2D {
public:
	virtual void load() override;
	virtual void unload() override;
	virtual void render() override;
	
	void setTexture(Ref<Texture> texture);
	Ref<Texture> getTexture();

	void setClip(const Rect& clip);
	virtual Rect getClip();

	Vec2 pivot{0.0, 0.0};

protected:
	void loadTexture();
	void unloadTexture();

protected:
	Rect clip;

	std::string load_path;
	Ref<Texture> texture;
};


class SpriteSheet : public Sprite {
public:
	void setSheet(const std::vector<Rect>&);
	unsigned addFrame(const Rect&);
	Rect& getFrame(unsigned);

	Rect getClip() override;

public:
	unsigned current_frame;

protected:
	std::vector<Rect> frames;

};

}
