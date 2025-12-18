// TODO ownership: Heitor

#include "Rect.hpp"
#include "Vec2.hpp"
#include <algorithm>

using namespace engine;

Rect::Rect() :
	x(0),
	y(0),
	w(0),
	h(0)
{
}

Rect::Rect(
	const Vec2& origin, 
	const Vec2& dimensions
) :
	x(origin.x),
	y(origin.y),
	w(dimensions.x),
	h(dimensions.y)
{
}

Rect::Rect(
	float x,
	float y,
	float w,
	float h
) :
	x(x),
	y(y),
	w(w),
	h(h)
{
}

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

	Vec2 start(
		max(x, r.x),
		max(y, r.y)
	);

	Vec2 end(
		min(x+w, r.x + r.w),
		min(y+h, r.y + r.h)
	);

	if (start.x > end.x || start.y > end.y)
		return Rect();

	return Rect(
		start,
		end - start
	);
}


Vec2 Rect::getOrigin() const {
	return Vec2(x,y);
}

Vec2 Rect::getDimensions() const {
	return Vec2(w,h);
}

Vec2 Rect::getCenter() const {
	return getOrigin() + getDimensions()/2;
}

Vec2 Rect::getEnd() const {
	return getOrigin() + getDimensions();
}

void Rect::setOrigin(const Vec2& origin) {
	x = origin.x;
	y = origin.y;
}

void Rect::setDimensions(const Vec2& dimensions) {
	w = dimensions.x;
	h = dimensions.y;
}

void Rect::setCenter(const Vec2& center) {
	setOrigin(center - getDimensions()/2);
}

void Rect::setEnd(const Vec2& end) {
	setDimensions(end - getOrigin());
}


