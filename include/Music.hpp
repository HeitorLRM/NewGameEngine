#pragma once

#include "Resource.hpp"
#include "Ref.hpp"
#include <string>

namespace engine {

class Music : public Resource {
public:
	virtual const std::string& getResourceType() const override;

	virtual void load() override;
	virtual void unload() override;
	virtual void play(int loops = -1) = 0;
	virtual void stop() = 0;

	static Ref<Music> fromFile(const std::string& filepath);

public:
	std::string load_path;
};

}
