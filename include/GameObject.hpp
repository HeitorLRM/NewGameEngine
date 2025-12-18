// TODO ownership: Heitor

#pragma once

#include <memory>
#include <vector>
namespace engine {

class State;

class GameObject {
public:
	GameObject();

	virtual ~GameObject() = default;

	virtual void update(float delta_time);
	virtual void render();

	State* getState();
	void setState(State*);

	GameObject* getParent();
	void setParent(GameObject*);

	void addChild(std::shared_ptr<GameObject>);
	void addChild(std::shared_ptr<GameObject>, unsigned index);
	void removeChild(GameObject*);
	std::vector<std::shared_ptr<GameObject>>& getChildren();

private:
	std::vector<std::shared_ptr<GameObject>> children;

	State* state;
	GameObject* parent;
};

}

