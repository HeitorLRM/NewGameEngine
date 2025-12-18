// TODO ownership: Heitor

#include "State.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include <memory>

using namespace engine;
using std::shared_ptr;

State::State(Game* game) :
	game(game)
{

}

void State::update(float delta_time) {
	root->update(delta_time);
}

void State::render() {
	root->render();
}

Game* State::getGame() {
	return game;
}

GameObject* State::getRoot() {
	return root.get();
}

void State::setRoot(shared_ptr<GameObject> root) {
	this->root = root;

	getRoot()->setState(this);
}

