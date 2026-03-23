// TDOO ownership: Heitor

#include "Game.hpp"
#include "Stage.hpp"
#include "AppIO.hpp"
#include <algorithm>
#include <memory>
#include <vector>

using namespace engine;
using std::shared_ptr;
using std::find;

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

void Game::loadStage(Ref<Stage> stage) {
	loaded_stages.push_back(stage);
	// TODO error if already loaded
	loaded_stages.back().load_ref();
}

void Game::unloadStage(Ref<Stage> stage) {
	loaded_stages.erase(find(loaded_stages.begin(), loaded_stages.end(),stage));
	// TODO error if not loaded
	stage.unload_ref();
}

const std::vector<Ref<Stage>>& Game::getLoadedStages() {
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

void Game::close() {
	for (auto& stage : loaded_stages)
		unloadStage(stage);
	
	setInterface(nullptr);
}

