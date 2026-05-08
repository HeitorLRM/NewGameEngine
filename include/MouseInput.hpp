#pragma once

#include "Vec2.hpp"

namespace engine {

class MouseState {
public:
	Vec2 POS = Vec2::ZERO;
	Vec2 MOTION = Vec2::ZERO;
	Vec2 WHEEL_MOTION = Vec2::ZERO;
	union {
		struct {unsigned char BUTTONS = 0;};
		struct {
			unsigned char M1 : 1;
			unsigned char M2 : 1;
			unsigned char M3 : 1;
		};
	};

};

class MouseInput {
public:
	void update();

	void capture();
	void release();
	void show();
	void hide();

	MouseState isButtonDown() const;
	MouseState isButtonJustPressed() const;
	MouseState isButtonJustReleased() const;
	Vec2 getPosition() const;
	Vec2 getMotion() const;
	Vec2 getWheelMotion() const;

private:
	MouseState mouse_curr;
	MouseState mouse_prev;

};

}


