// TODO ownership: Heitor

#pragma once

#include "Vec2.hpp"

namespace engine {

class Rect {
public:
	Rect();
	Rect(
		float x, 
		float y,
		float w,
		float h
	);
	Rect(
		const Vec2& origin, 
		const Vec2& dimensions
	);

	float area() const;
	bool contains(const Vec2&) const;
	bool contains(const Rect&) const;
	bool intersects(const Rect&) const;
	Rect intersection(const Rect&) const;

	Vec2 getOrigin() const;
	Vec2 getDimensions() const;
	Vec2 getCenter() const;
	Vec2 getEnd() const;
	void setOrigin(const Vec2&);
	void setDimensions(const Vec2&);
	void setCenter(const Vec2&);
	void setEnd(const Vec2&);

public:
	float x, y, w, h;
};

}

