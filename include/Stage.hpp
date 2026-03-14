// TODO ownership: Heitor

#pragma once
#include "GameObject.hpp"
#include "Ref.hpp"
namespace engine {

class Game;

class Stage : public Resource {
public:
	Stage(Game* game);

	virtual void load() override;
	virtual void unload() override;
	virtual void update(float delta_time);
	virtual void render();

	Game* getGame();

	GameObject* getRoot();
	void setRoot(Ref<GameObject>);

protected:
	Game* game;

	Ref<GameObject> root;

};

}