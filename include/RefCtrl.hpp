#pragma once

namespace engine {

class Resource;

class RefCtrl {
public:
	void load_res();
	void unload_res();

public:
	Resource* resource;
	int ref_count;
	int load_count;
};

}
