// TDOO ownership: Heitor

#include "Game.hpp"
#include "Stage.hpp"
#include "AppIO.hpp"
#include <memory>

using namespace engine;
using std::shared_ptr;

Game::Game() :
	quit_requested(false),
	interface(nullptr)
{
}

void Game::requestQuit() {
	quit_requested = true;
}

bool Game::shouldQuit() {
	return
		// Check if interface has requested to stop the game
		(interface && interface->shouldClose()) ||

		// Check if game logic requested stop
		quit_requested
	;
}

shared_ptr<AppIO> Game::getInterface() {
	return interface;
}

void Game::loadStage(shared_ptr<Stage> stage) {
	loaded_stages.insert(stage);
	// TODO error if already in set
	stage->load();
}

void Game::unloadStage(shared_ptr<Stage> stage) {
	loaded_stages.erase(stage);
	// TODO error if not in set
	stage->unload();
}


const std::set<std::shared_ptr<Stage>>& Game::getLoadedStages() {
	return loaded_stages;
}

void Game::setInterface(shared_ptr<AppIO> interface) {
	this->interface = interface;
}

void Game::run() {
	init();

	while (!shouldQuit()) {
		mainLoop();
	}

	close();
}

void Game::mainLoop() {
	if (interface)
		interface->update();

	for (auto stage : loaded_stages) {
		stage->update(1.0/30.0);
		stage->render();
	}

	if (interface)
		interface->render();
}

