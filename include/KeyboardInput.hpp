#pragma once

namespace engine {

class KeyboardState {
public:
	KeyboardState operator| (const KeyboardState&) const;
	KeyboardState operator& (const KeyboardState&) const;
	KeyboardState operator^ (const KeyboardState&) const;
	KeyboardState operator~ () const;

	union {
		struct {unsigned char keys[8] = {};};
		struct {
			unsigned char A : 1;
			unsigned char B : 1;
			unsigned char C : 1;
			unsigned char D : 1;
			unsigned char E : 1;
			unsigned char F : 1;
			unsigned char G : 1;
			unsigned char H : 1;
			unsigned char I : 1;
			unsigned char J : 1;
			unsigned char K : 1;
			unsigned char L : 1;
			unsigned char M : 1;
			unsigned char N : 1;
			unsigned char O : 1;
			unsigned char P : 1;
			unsigned char Q : 1;
			unsigned char R : 1;
			unsigned char S : 1;
			unsigned char T : 1;
			unsigned char U : 1;
			unsigned char V : 1;
			unsigned char W : 1;
			unsigned char X : 1;
			unsigned char Y : 1;
			unsigned char Z : 1;
			unsigned char _0 : 1;
			unsigned char _1 : 1;
			unsigned char _2 : 1;
			unsigned char _3 : 1;
			unsigned char _4 : 1;
			unsigned char _5 : 1;
			unsigned char _6 : 1;
			unsigned char _7 : 1;
			unsigned char _8 : 1;
			unsigned char _9 : 1;
			unsigned char UP	: 1;
			unsigned char DOWN	: 1;
			unsigned char LEFT	: 1;
			unsigned char RIGHT	: 1;
			unsigned char SPACEBAR	: 1;
			unsigned char ESC 		: 1;
			unsigned char ENTER 	: 1;
			unsigned char SHIFT 	: 1;
			unsigned char CTRL	 	: 1;
		};
	};
};

class KeyboardInput {
public:
	void update(const KeyboardState& new_curr);

	const KeyboardState& isKeyDown() const;
	const KeyboardState& isKeyJustPressed() const;
	const KeyboardState& isKeyJustReleased() const;

	const KeyboardState& getState() const;


private:
	KeyboardState keyboard_prev;
	KeyboardState keyboard_curr;
	KeyboardState keyboard_just_pressed;
	KeyboardState keyboard_just_released;
};

}
