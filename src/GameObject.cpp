// TODO ownership: Heitor

#include "GameObject.hpp"
#include "Game.hpp"
#include "Ref.hpp"
#include <iterator>

using namespace engine;

using std::list;

GameObject::GameObject() :
	stage(nullptr),
	parent(nullptr)
{
}

void GameObject::setStage(Stage* stage) {
	this->stage = stage;

	for (auto& child : children)
		child->setStage(stage);
}

Stage* GameObject::getStage() {
	return stage;
}

void GameObject::setParent(GameObject* parent) {
	// Is already child of parent
	if (this->parent == parent)
		return;

	if (this->parent)
		this->parent->removeChild(this);
	
	this->parent = parent;

	if (parent)
		setStage(parent->getStage());
}

GameObject* GameObject::getParent() {
	return parent;
}

void GameObject::addChild(Ref<GameObject> child) {
	addChild(child, children.size());
}

void GameObject::addChild(Ref<GameObject> child, unsigned index) {
	// Do not add the same child twice
	if (child->getParent() == this)
		return;

	child->setParent(this);

	auto it = children.begin();
	std::advance(it, index);
	it = children.insert(it, child);

	if (is_loaded)
		it->load_ref();
}

void GameObject::removeChild(GameObject* child) {
	auto it = children.begin();
	for (; it != children.end(); it++)
		if (it->get() == child)
			break;

	if (it == children.end())
		return;

	child->parent = nullptr;

	children.erase(it);
}

list<Ref<GameObject>>& GameObject::getChildren() {
	return children;
}

void GameObject::update(float delta_time) {
	for (auto& child : children) {
		child->update(delta_time);
	}
}

void GameObject::render() {
	for (auto& child : children) {
		child->render();
	}
}

void GameObject::load() {
	Resource::load();
	for (auto& child : children)
		child.load_ref();
}

void GameObject::unload() {
	Resource::unload();
	for (auto& child : children)
		child.unload_ref();
}
