// TODO ownership: Heitor

#pragma once
#include <memory>
namespace engine {

class Game;
class GameObject;

class Stage {
public:
	Stage(Game* game);

	virtual void update(float delta_time);
	virtual void render();
	virtual void load();
	virtual void unload();

	Game* getGame();

	GameObject* getRoot();
	void setRoot(std::shared_ptr<GameObject>);

protected:
	Game* game;

	std::shared_ptr<GameObject> root;

};

}