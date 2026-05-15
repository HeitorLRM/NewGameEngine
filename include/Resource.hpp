#pragma once

#include <string>

namespace engine {

class Resource {
public:
	virtual ~Resource() = default;

	virtual const std::string& getResourceType() const;
	explicit operator std::string() const;


	virtual void load();
	virtual void unload();

	int ref_count = 0;
	int load_count = 0;
	bool is_loaded = false;
};

}

std::ostream& operator<<(std::ostream& os, const engine::Resource& r);
