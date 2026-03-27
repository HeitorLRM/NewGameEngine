// TODO ownership: Heitor

#pragma once

#include "Ref.hpp"
namespace engine {

class GameObject;

class Game {
public:
	Game() = delete;

	static void run();
	static void requestQuit();
	
	static void loadRoot(Ref<GameObject>);
	static void unloadRoot();
	static Ref<GameObject> getRoot();

private:
	static void init();
	static void close();

	static void mainLoop();
	static bool shouldQuit();
	
public:
	static void (*init_callback)();
	static void (*close_callback)();

private:
	static bool quit_requested;
	static Ref<GameObject> root;
};

}
