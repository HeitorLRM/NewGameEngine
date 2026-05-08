#include "KeyboardInput.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>

using namespace engine;

// KeyboardInput --------------------------------------------------------

void KeyboardInput::update() {
	keyboard_prev = keyboard_curr;

	SDL_Event event;
	SDL_PumpEvents();
	while (
		SDL_PeepEvents(
			&event, 
			1, 
			SDL_GETEVENT, 
			SDL_EVENT_KEY_DOWN, 
			SDL_EVENT_KEY_UP)
	) {

		unsigned char key_state = event.key.down ? 1 : 0;

		#define KEYCASE(sdl_key, key) \
			case (sdl_key):\
				keyboard_curr.key = key_state;\
				break;

		switch (event.key.key) {
			KEYCASE(SDLK_A, A);
			KEYCASE(SDLK_B, B);
			KEYCASE(SDLK_C, C);
			KEYCASE(SDLK_D, D);
			KEYCASE(SDLK_E, E);
			KEYCASE(SDLK_F, F);
			KEYCASE(SDLK_G, G);
			KEYCASE(SDLK_H, H);
			KEYCASE(SDLK_I, I);
			KEYCASE(SDLK_J, J);
			KEYCASE(SDLK_K, K);
			KEYCASE(SDLK_L, L);
			KEYCASE(SDLK_M, M);
			KEYCASE(SDLK_N, N);
			KEYCASE(SDLK_O, O);
			KEYCASE(SDLK_P, P);
			KEYCASE(SDLK_Q, Q);
			KEYCASE(SDLK_R, R);
			KEYCASE(SDLK_S, S);
			KEYCASE(SDLK_T, T);
			KEYCASE(SDLK_U, U);
			KEYCASE(SDLK_V, V);
			KEYCASE(SDLK_W, W);
			KEYCASE(SDLK_X, X);
			KEYCASE(SDLK_Y, Y);
			KEYCASE(SDLK_Z, Z);
			KEYCASE(SDLK_0, _0);
			KEYCASE(SDLK_1, _1);
			KEYCASE(SDLK_2, _2);
			KEYCASE(SDLK_3, _3);
			KEYCASE(SDLK_4, _4);
			KEYCASE(SDLK_5, _5);
			KEYCASE(SDLK_6, _6);
			KEYCASE(SDLK_7, _7);
			KEYCASE(SDLK_8, _8);
			KEYCASE(SDLK_9, _9);
			KEYCASE(SDLK_UP, UP);
			KEYCASE(SDLK_DOWN, DOWN);
			KEYCASE(SDLK_LEFT, LEFT);
			KEYCASE(SDLK_RIGHT, RIGHT);
			KEYCASE(SDLK_SPACE, SPACEBAR);
			KEYCASE(SDLK_LSHIFT, SHIFT);
			KEYCASE(SDLK_LCTRL, CTRL);
			KEYCASE(SDLK_ESCAPE, ESC);
		}

		#undef KEYCASE

		SDL_PumpEvents();
	}
}

KeyboardState KeyboardInput::isKeyDown() const{
	return keyboard_curr;
}

KeyboardState KeyboardInput::isKeyJustPressed() const{
	return ~keyboard_prev & keyboard_curr;
}

KeyboardState KeyboardInput::isKeyJustReleased() const{
	return keyboard_prev & ~keyboard_curr;
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
