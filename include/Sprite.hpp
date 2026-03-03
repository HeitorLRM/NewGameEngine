// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"
#include "Object2D.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include <memory>
#include <vector>

namespace engine {

class Sprite : public Object2D {
public:
	void render() override;
	
	void setTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> getTexture();

	void setClip(const Rect& clip);
	virtual Rect getClip();

	Vec2 pivot{0.0, 0.0};

protected:
	Rect clip;

	std::shared_ptr<Texture> texture;
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
