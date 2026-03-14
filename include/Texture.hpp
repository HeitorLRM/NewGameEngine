#pragma once

#include "AppIO.hpp"
#include "Rect.hpp"
#include "Ref.hpp"
#include "Vec2.hpp"

#include <memory>

namespace engine {

class Texture : public Resource{
public:
	// Abstract
	virtual void render(const Rect& clip, const Rect& dst) = 0; // TODO Reci
	virtual void renderQuad(const Vec2 (&vertices)[4], const Vec2 (&uvs)[4]) = 0;

	static Ref<Texture> loadFromFile(const std::string& filepath, std::weak_ptr<AppIO> interface);

	Vec2 getDimensions();

protected:
	Vec2 dimensions; // TODO Vec2i

};

}