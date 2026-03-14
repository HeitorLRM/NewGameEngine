#pragma once

#include "RefCtrl.hpp"

#include <iostream>

namespace engine {

class Resource {
protected:
	virtual void load() {
		is_loaded = true;
		std::cout << "\tResource Loaded" << std::endl;
	}

	virtual void unload() {
		is_loaded = false;
		std::cout << "\tResource Unloaded" << std::endl;
	}

public:
	bool is_loaded = false;

	friend RefCtrl;
};

}
