// TODO ownership: Heitor

#include "Stage.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Resource.hpp"

using namespace engine;

Stage::Stage(Game* game) :
	game(game),
	root(nullptr)
{

}

void Stage::update(float delta_time) {
	root->update(delta_time);
}

void Stage::render() {
	root->render();
}

void Stage::load() {
	Resource::load();
	root.load_ref();
}

void Stage::unload() {
	Resource::unload();
	root.unload_ref();
}

Game* Stage::getGame() {
	return game;
}

GameObject* Stage::getRoot() {
	return root.get();
}

void Stage::setRoot(Ref<GameObject> root) {
	if (this->root)
		this->root.unload_ref();

	this->root = root;

	root->setStage(this);
	if (is_loaded)
		root.load_ref();
}

