// TODO ownership: Heitor

#pragma once

#include "Game.hpp"
#include "Ref.hpp"
#include <list>
namespace engine {

class Stage;
class GameObject : public Resource {
public:
	GameObject();

	virtual ~GameObject() = default;

	virtual void load() override;
	virtual void unload() override;
	virtual void update(float delta_time);
	virtual void pre_render();
	virtual void render();

	Stage* getStage();
	void setStage(Stage*);

	GameObject* getParent();
	virtual void setParent(GameObject*);

	void addChild(Ref<GameObject>);
	void addChild(Ref<GameObject>, unsigned index);
	void removeChild(GameObject*);
	Ref<GameObject> getChild(GameObject*);
	std::list<Ref<GameObject>>& getChildren();

private:
	std::list<Ref<GameObject>> children;

	Stage* stage;
	GameObject* parent;
};

}

