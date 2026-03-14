#include "Resource.hpp"

using namespace engine;

void RefCtrl::load_res() {
	resource->load();
}

void RefCtrl::unload_res() {
	resource->unload();
}
