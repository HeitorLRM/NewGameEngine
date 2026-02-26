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

	Vec2 getCenter() const;
	Vec2 getEnd() const;
	void setCenter(const Vec2&);
	void setEnd(const Vec2&);

public:
	float& x() {return origin.x;};
	float& y() {return origin.y;};
	float& w() {return dimensions.x;};
	float& h() {return dimensions.y;};
	const float& x() const {return origin.x;} ;
	const float& y() const {return origin.y;} ;
	const float& w() const {return dimensions.x;} ;
	const float& h() const {return dimensions.y;} ;

	Vec2 origin, dimensions;
};

}

