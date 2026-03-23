// TODO ownership: Heitor

#include "Stage.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Resource.hpp"

using namespace engine;

Stage::Stage(Game* game) :
	game(game)
{
}

void Stage::update(float delta_time) {
	if (root)
		root->update(delta_time);
}

void Stage::render() {
	if (root)
		root->render();
}

void Stage::load() {
	Resource::load();

	if (root)
		root.load_ref();
}

void Stage::unload() {
	Resource::unload();
	
	if (root)
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

	this->root->setStage(this);
	if (is_loaded)
		this->root.load_ref();
}

