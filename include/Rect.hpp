// TODO ownership: Heitor

#pragma once

#include "Vec2.hpp"

namespace engine {

class Rect {
public:
	float area() const;
	bool contains(const Vec2&) const;
	bool contains(const Rect&) const;
	bool intersects(const Rect&) const;
	Rect intersection(const Rect&) const;

	Vec2 getCenter() const;
	Vec2 getEnd() const;
	void setCenter(const Vec2&);
	void setEnd(const Vec2&);

public:
	union {
		struct {Vec2 origin, dimensions;};
		struct {float x, y, w, h;};
	};
};

}

