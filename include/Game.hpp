// TODO ownership: Heitor

#pragma once

#include "Ref.hpp"
namespace engine {

class Stage;

class Game {
public:
	Game() = delete;

	static void run();
	static void requestQuit();
	
	static void loadStage(Ref<Stage>);
	static void unloadStage();
	static Ref<Stage> getStage();

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
	static Ref<Stage> loaded_stage;
};

}
