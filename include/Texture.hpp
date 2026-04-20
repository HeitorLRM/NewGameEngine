#pragma once

#include "AppIO.hpp"
#include "Rect.hpp"
#include "Ref.hpp"
#include "Vec2.hpp"

#include <array>
#include <string>

namespace engine {

class Texture : public Resource {
public:
	virtual const std::string& getResourceType() const override;

	virtual void load() override;
	virtual void unload() override;
	virtual void render(const Rect& clip, const Rect& dst) = 0;
	virtual void renderQuad(const std::array<Vec2, 4>& vertices, const std::array<Vec2, 4>& uvs) = 0;

	static Ref<Texture> fromFile(const std::string& filepath);

public:
	std::string load_path;
	Vec2 dimensions;
};

}
