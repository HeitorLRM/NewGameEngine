// TDOO ownership: Heitor

#include "Game.hpp"
#include "AppIO.hpp"
#include "GameObject.hpp"

using namespace engine;

bool Game::quit_requested = false;
Ref<GameObject> Game::root;


void Game::requestQuit() {
	quit_requested = true;
}

bool Game::shouldQuit() {
	return (
		AppIO::shouldClose() ||
		quit_requested
	);
}

void Game::loadRoot(Ref<GameObject> r) {
	if (root)
		unloadRoot();

	root = r;

	root.load_ref();
}

void Game::unloadRoot() {
	root.unload_ref();
}

Ref<GameObject> Game::getRoot() {
	return root;
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

	if (root) {
		root->update(1.0/30.0);
		root->render();
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

	unloadRoot();
	AppIO::close();
}

