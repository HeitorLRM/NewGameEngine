#pragma once

#include "RefCtrl.hpp"

#include <string>

namespace engine {

class Resource {
protected:
	virtual void load() {
		is_loaded = true;
	}

	virtual void unload() {
		is_loaded = false;
	}

public:
	bool is_loaded = false;
	std::string source = "";

	friend RefCtrl;
};

}
