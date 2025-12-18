// TODO ownership: Heitor

#include "GameObject.hpp"
#include "State.hpp"
#include <memory>
#include <vector>

using namespace engine;

using std::shared_ptr;
using std::vector;

GameObject::GameObject() :
	state(nullptr),
	parent(nullptr)
{
}

void GameObject::setState(State* state) {
	this->state = state;

	for (auto& child : children)
		child->setState(state);
}

State* GameObject::getState() {
	return state;
}

void GameObject::setParent(GameObject* parent) {
	// Is already child of parent
	if (this->parent == parent)
		return;

	if (this->parent)
		this->parent->removeChild(this);
	
	this->parent = parent;

	if (parent)
		setState(parent->getState());
}

GameObject* GameObject::getParent() {
	return parent;
}

void GameObject::addChild(shared_ptr<GameObject> child) {
	addChild(child, children.size());
}

void GameObject::addChild(shared_ptr<GameObject> child, unsigned index) {
	// Do not add the same child twice
	if (child->getParent() == this)
		return;

	child->setParent(this);
	
	children.insert(children.begin() + index, child);
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

vector<shared_ptr<GameObject>>& GameObject::getChildren() {
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


