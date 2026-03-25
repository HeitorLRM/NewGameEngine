// TDOO ownership: Heitor

#include "Game.hpp"
#include "Stage.hpp"
#include "AppIO.hpp"

using namespace engine;

bool Game::quit_requested = false;
Ref<Stage> Game::loaded_stage;


void Game::requestQuit() {
	quit_requested = true;
}

bool Game::shouldQuit() {
	return (
		AppIO::shouldClose() ||
		quit_requested
	);
}

void Game::loadStage(Ref<Stage> s) {
	loaded_stage = s;
	loaded_stage.load_ref();
}

void Game::unloadStage() {
	loaded_stage.unload_ref();
}

Ref<Stage> Game::getStage() {
	return loaded_stage;
}

void Game::run() {
	init();

	while (!shouldQuit()) {
		mainLoop();
	}

	close();
}

void Game::mainLoop() {
	AppIO::update();

	if (loaded_stage) {
		loaded_stage->update(1.0/30.0);
		loaded_stage->render();
	}

	AppIO::render();
}

void Game::init() {
	AppIO::init();

	if (init_callback)
		init_callback();
}

void Game::close() {
	if (close_callback)
		close_callback();

	unloadStage();
	AppIO::close();
}

