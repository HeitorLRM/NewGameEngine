#include "Resource.hpp"
#include <ostream>
#include <string>

using namespace engine;
using std::string;
using std::to_string;
using std::ostream;

void Resource::load() {
	is_loaded = true;
}

void Resource::unload() {
	is_loaded = false;
}

const string& Resource::getResourceType() const {
	static const string RES_TYPE = "Resource";
	return RES_TYPE;
}

Resource::operator std::string() const {
	return getResourceType();
}

ostream& operator<<(ostream& os, const Resource& r) {
	return os << "<" << (std::string)r << ":" + to_string((long)&r) << ">";
}
