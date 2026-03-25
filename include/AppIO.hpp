// TODO ownership: Heitor

#pragma once

#include "KeyboardInput.hpp"

namespace engine {

class Texture;

namespace AppIO {

extern void init();
extern void close();
extern void update();
extern void render();
extern bool shouldClose();

extern KeyboardInput keyboard;

};

}
