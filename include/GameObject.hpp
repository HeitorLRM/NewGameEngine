// TODO ownership: Heitor

#pragma once

#include "Game.hpp"
#include "KeyboardInput.hpp"
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
	virtual void render();

	Stage* getStage();
	void setStage(Stage*);

	GameObject* getParent();
	virtual void setParent(GameObject*);

	Game* getGame() const;
	const KeyboardInput* getKeyboardInput() const;

	void addChild(Ref<GameObject>);
	void addChild(Ref<GameObject>, unsigned index);
	void removeChild(GameObject*);
	std::list<Ref<GameObject>>& getChildren();

private:
	std::list<Ref<GameObject>> children;

	Stage* stage;
	GameObject* parent;
};

}

