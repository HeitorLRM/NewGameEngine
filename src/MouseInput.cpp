#include "MouseInput.hpp"
#include "SDL_AppIO.hpp"
#include "Vec2.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

using namespace engine;


void MouseInput::update() {
	mouse_prev = mouse_curr;
	mouse_curr.MOTION = Vec2::ZERO;
	mouse_curr.WHEEL_MOTION = Vec2::ZERO;

	SDL_Event event;
	SDL_PumpEvents();
	while (
		SDL_PeepEvents(
			&event, 
			1, 
			SDL_GETEVENT, 
			SDL_EVENT_MOUSE_MOTION, 
			SDL_EVENT_MOUSE_WHEEL
		)
	) {
		switch (event.type) {
			case SDL_EVENT_MOUSE_MOTION:
				mouse_curr.POS = {event.motion.x, event.motion.y};
				mouse_curr.MOTION = {event.motion.xrel, event.motion.yrel};
				break;

			case SDL_EVENT_MOUSE_WHEEL:
				mouse_curr.WHEEL_MOTION = {event.wheel.x, event.wheel.y};
				break;
			
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			case SDL_EVENT_MOUSE_BUTTON_UP:
				unsigned char button_state = event.button.down ? 1 : 0;

				#define BUTTONCASE(sdl_button, button) \
					case (sdl_button):\
						mouse_curr.button = button_state;\
						break;
		
				switch (event.button.button) {
					BUTTONCASE(1, M1);
					BUTTONCASE(3, M2);
					BUTTONCASE(2, M3);
					default: break;
				}

				#undef BUTTONCASE
				break;
		}

		SDL_PumpEvents();
	}
}

void MouseInput::capture() {
	SDL_SetWindowRelativeMouseMode(AppIO::SDL::window, true);
}

void MouseInput::release() {
	SDL_SetWindowRelativeMouseMode(AppIO::SDL::window, false);
}

void MouseInput::show() {
	SDL_ShowCursor();
}

void MouseInput::hide() {
	SDL_HideCursor();
}

MouseState MouseInput::isButtonDown() const {
	return MouseState{
		.BUTTONS = mouse_curr.BUTTONS
	};
}

MouseState MouseInput::isButtonJustPressed() const {
	return MouseState{
		.BUTTONS = static_cast<unsigned char>(~mouse_prev.BUTTONS & mouse_curr.BUTTONS)
	};
}

MouseState MouseInput::isButtonJustReleased() const {
	return MouseState{
		.BUTTONS = static_cast<unsigned char>(mouse_prev.BUTTONS & ~mouse_curr.BUTTONS)
	};
}

Vec2 MouseInput::getPosition() const {
	return mouse_curr.POS;
}

Vec2 MouseInput::getMotion() const {
	return mouse_curr.MOTION;
}

Vec2 MouseInput::getWheelMotion() const {
	return mouse_curr.WHEEL_MOTION;
}

