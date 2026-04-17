#pragma once

#include "RefCtrl.hpp"

#include <string>

namespace engine {

class Resource {
public:
	virtual ~Resource() = default;

	virtual const std::string& getResourceType() const;
	explicit operator std::string() const;

protected:
	virtual void load();
	virtual void unload();

public:

	bool is_loaded = false;
	std::string source = "";

	friend RefCtrl;
};

}

std::ostream& operator<<(std::ostream& os, const engine::Resource& r);
