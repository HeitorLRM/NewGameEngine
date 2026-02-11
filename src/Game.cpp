// TDOO ownership: Heitor

#include "Game.hpp"
#include "State.hpp"
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

weak_ptr<State> Game::getState() {
	return state;
}

weak_ptr<AppIO> Game::getInterface() {
	return interface;
}

void Game::setState(shared_ptr<State> state) {
	this->state = state;
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
	if (state) {
		state->update(1.0/30.0);
		state->render();
	}

	if (interface)
		interface->render();
}

