#pragma once

#include "Vec2.hpp"

namespace engine {

class GamepadState {
public:
	Vec2 JOY_L = Vec2::ZERO;
	Vec2 JOY_R = Vec2::ZERO;
	float L2 = 0;
	float R2 = 0;
	union {
		struct {unsigned short BUTTONS = 0;};
		struct {
			unsigned char DPAD_UP : 1;
			unsigned char DPAD_DOWN : 1;
			unsigned char DPAD_LEFT : 1;
			unsigned char DPAD_RIGHT : 1;
			unsigned char START : 1;
			unsigned char SELECT : 1;
			unsigned char L1 : 1;
			unsigned char R1 : 1;
			unsigned char JOY_L_BTN : 1;
			unsigned char JOY_R_BTN : 1;
			unsigned char A : 1;
			unsigned char B : 1;
			unsigned char X : 1;
			unsigned char Y : 1;
		};
	};
};

class GamepadInput {
public:
	void update();

	GamepadState isButtonDown() const;
	GamepadState isButtonJustPressed() const;
	GamepadState isButtonJustReleased() const;
	Vec2 getJoyLeft() const;
	Vec2 getJoyRight() const;
	float getTriggerL2() const;
	float getTriggerR2() const;
	

private:
	GamepadState gamepad_curr;
	GamepadState gamepad_prev;

};

}


