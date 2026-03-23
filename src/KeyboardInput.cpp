#include "KeyboardInput.hpp"

using namespace engine;

// KeyboardInput --------------------------------------------------------

void KeyboardInput::update(const KeyboardState& new_curr) {
	keyboard_prev = keyboard_curr;
	keyboard_curr = new_curr;
	keyboard_just_pressed = ~keyboard_prev & keyboard_curr;
	keyboard_just_released = keyboard_prev & ~keyboard_curr;
}

const KeyboardState& KeyboardInput::isKeyDown() const{
	return keyboard_curr;
}

const KeyboardState& KeyboardInput::isKeyJustPressed() const{
	return keyboard_just_pressed;
}

const KeyboardState& KeyboardInput::isKeyJustReleased() const{
	return keyboard_just_released;
}

const KeyboardState& KeyboardInput::getState() const {
	return keyboard_curr;
}

// KeyboardState --------------------------------------------------------

KeyboardState KeyboardState::operator&(const KeyboardState& k) const {
	KeyboardState ret = k;
	for (int i=0; i<sizeof(ret); i++) {
		ret.keys[i] &= keys[i];
	}
	return ret;
}

KeyboardState KeyboardState::operator|(const KeyboardState& k) const {
	KeyboardState ret = k;
	for (int i=0; i<sizeof(ret); i++) {
		ret.keys[i] |= keys[i];
	}
	return ret;
}

KeyboardState KeyboardState::operator^(const KeyboardState& k) const {
	KeyboardState ret = k;
	for (int i=0; i<sizeof(ret); i++) {
		ret.keys[i] ^= keys[i];
	}
	return ret;
}

KeyboardState KeyboardState::operator~() const {
	KeyboardState ret;
	for (int i=0; i<sizeof(ret); i++) {
		ret.keys[i] = ~keys[i];
	}
	return ret;
}
