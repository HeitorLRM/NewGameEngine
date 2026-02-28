// TODO ownership: Heitor

#include "Rect.hpp"
#include "Vec2.hpp"
#include <algorithm>

using namespace engine;

float Rect::area() const {
	return w * h;
}

bool Rect::contains(const Vec2& point) const {
	return
		x <= point.x && point.x < x+w &&
		y <= point.y && point.y < y+h
	;
}

bool Rect::contains(const Rect& r) const {
	return r.area() == intersection(r).area();
}

bool Rect::intersects(const Rect& r) const {
	return intersection(r).area() > 0;
}

Rect Rect::intersection(const Rect& r) const {
	using std::min;
	using std::max;

	Vec2 start{
		max(x, r.x),
		max(y, r.y)
	};

	Vec2 end{
		min(x+w, r.x + r.w),
		min(y+h, r.y + r.h)
	};

	if (start.x > end.x || start.y > end.y)
		return Rect();

	return Rect{
		start,
		end - start
	};
}

Vec2 Rect::getCenter() const {
	return origin + dimensions/2;
}

Vec2 Rect::getEnd() const {
	return origin + dimensions;
}

void Rect::setCenter(const Vec2& center) {
	origin = center - dimensions/2;
}

void Rect::setEnd(const Vec2& end) {
	dimensions = end - origin;
}


