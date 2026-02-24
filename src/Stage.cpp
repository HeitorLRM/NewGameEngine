// TODO ownership: Heitor

#include "Stage.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include <memory>

using namespace engine;
using std::shared_ptr;

Stage::Stage(Game* game) :
	game(game)
{

}

void Stage::update(float delta_time) {
	root->update(delta_time);
}

void Stage::render() {
	root->render();
}

Game* Stage::getGame() {
	return game;
}

GameObject* Stage::getRoot() {
	return root.get();
}

void Stage::setRoot(shared_ptr<GameObject> root) {
	this->root = root;

	getRoot()->setStage(this);
}

