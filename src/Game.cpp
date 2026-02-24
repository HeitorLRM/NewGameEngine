// TDOO ownership: Heitor

#include "Game.hpp"
#include "Stage.hpp"
#include "AppIO.hpp"
#include <memory>

using namespace engine;
using std::shared_ptr;
using std::weak_ptr;

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
		(getInterface().lock() && getInterface().lock()->shouldClose()) ||

		// Check if game logic requested
		quit_requested
	;
}

weak_ptr<Stage> Game::getStage() {
	return stage;
}

weak_ptr<AppIO> Game::getInterface() {
	return interface;
}

void Game::setStage(shared_ptr<Stage> stage) {
	this->stage = stage;
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
	if (stage) {
		stage->update(1.0/30.0);
		stage->render();
	}

	if (interface)
		interface->render();
}

