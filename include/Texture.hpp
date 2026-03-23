#pragma once

#include "AppIO.hpp"
#include "Rect.hpp"
#include "Ref.hpp"
#include "Vec2.hpp"

#include <memory>
#include <string>

namespace engine {

class Texture : public Resource {
// Abstract
public:
	virtual void load() override;
	virtual void unload() override;
	virtual void render(const Rect& clip, const Rect& dst) = 0;
	virtual void renderQuad(const Vec2 (&vertices)[4], const Vec2 (&uvs)[4]) = 0;

	static Ref<Texture> fromFile(const std::string& filepath, std::weak_ptr<AppIO> interface);

	Vec2 getDimensions();

protected:

protected:
	std::string load_path;

	Vec2 dimensions;
};

}