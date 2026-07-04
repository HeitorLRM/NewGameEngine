#include "GamepadInput.hpp"
#include "SDL_AppIO.hpp"
#include "SDL_gamepad.h"
#include "Vec2.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

using namespace engine;
using AppIO::SDL::sdl_gamepad;

void GamepadInput::update() {
	gamepad_prev = gamepad_curr;

	SDL_Event event;
	SDL_PumpEvents();
	while (
		SDL_PeepEvents(
			&event, 
			1, 
			SDL_GETEVENT, 
			SDL_EVENT_FIRST, 
			SDL_EVENT_LAST
		)
	) {
		switch (event.type) {
			case SDL_EVENT_GAMEPAD_ADDED:
				sdl_gamepad = SDL_OpenGamepad(event.gdevice.which);
				break;

			case SDL_EVENT_GAMEPAD_REMOVED:
				sdl_gamepad = nullptr;
				break;
		}
		SDL_PumpEvents();
	}

	if (!sdl_gamepad)
		return;

	gamepad_curr.JOY_L = Vec2{
		(float)SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_LEFTX),
		-(float)SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_LEFTY),
	} / 32767.0f;
	gamepad_curr.JOY_R = Vec2{
		(float)SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_RIGHTX),
		-(float)SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_RIGHTY),
	} / 32767.0f;
	gamepad_curr.L2 = SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) / 32767.0f;
	gamepad_curr.R2 = SDL_GetGamepadAxis(sdl_gamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) / 32767.0f;

	#define GET_BTN(button, button_sdl) \
		gamepad_curr.button = SDL_GetGamepadButton(sdl_gamepad, button_sdl);

	GET_BTN(DPAD_UP, SDL_GAMEPAD_BUTTON_DPAD_UP);
	GET_BTN(DPAD_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN);
	GET_BTN(DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT);
	GET_BTN(DPAD_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
	GET_BTN(START, SDL_GAMEPAD_BUTTON_START);
	GET_BTN(SELECT, SDL_GAMEPAD_BUTTON_BACK);
	GET_BTN(L1, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
	GET_BTN(R1, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);
	GET_BTN(JOY_L_BTN, SDL_GAMEPAD_BUTTON_LEFT_STICK);
	GET_BTN(JOY_R_BTN, SDL_GAMEPAD_BUTTON_RIGHT_STICK);
	GET_BTN(A, SDL_GAMEPAD_BUTTON_EAST);
	GET_BTN(B, SDL_GAMEPAD_BUTTON_SOUTH);
	GET_BTN(X, SDL_GAMEPAD_BUTTON_NORTH);
	GET_BTN(Y, SDL_GAMEPAD_BUTTON_WEST);

	#undef GET_BTN
}

GamepadState GamepadInput::isButtonDown() const {
	return GamepadState{
		.BUTTONS = gamepad_curr.BUTTONS
	};
}

GamepadState GamepadInput::isButtonJustPressed() const {
	return GamepadState{
		.BUTTONS = static_cast<unsigned short>(~gamepad_prev.BUTTONS & gamepad_curr.BUTTONS)
	};
}

GamepadState GamepadInput::isButtonJustReleased() const {
	return GamepadState{
		.BUTTONS = static_cast<unsigned short>(gamepad_prev.BUTTONS & ~gamepad_curr.BUTTONS)
	};
}

Vec2 GamepadInput::getJoyLeft() const {
	return gamepad_curr.JOY_L;
}

Vec2 GamepadInput::getJoyRight() const {
	return gamepad_curr.JOY_R;
}

float GamepadInput::getTriggerL2() const {
	return gamepad_curr.L2;
}

float GamepadInput::getTriggerR2() const {
	return gamepad_curr.R2;
}

