// TODO ownership: Heitor

#pragma once

#include "Object2D.hpp"
#include "Rect.hpp"
#include "Vec2.hpp"
#include <memory>
#include <vector>

namespace engine {

class Texture {
public:
	// Abstract
	virtual bool loadFromFile(const std::string&) = 0;
	virtual void render(const Rect& clip, const Rect& dst) = 0; // TODO Reci

	Vec2 getDimensions();

protected:
	Vec2 dimensions; // TODO Vec2i

};


class Sprite : public Object2D {
public:
	void render() override;
	
	void setTexture(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> getTexture();

	void setClip(const Rect& clip);
	virtual Rect getClip();

protected:
	Rect clip;

	std::shared_ptr<Texture> texture;
};


class SpriteSheet : public Sprite {
public:
	void setSheet(const std::vector<Rect>&);
	unsigned addFrame(const Rect&);
	Rect& getFrame(unsigned);

	void setCurrentFrame(unsigned);
	unsigned getCurrentFrame();

	Rect getClip() override;

protected:
	unsigned current_frame;
	std::vector<Rect> frames;

};

}
