// TODO ownership: Heitor

#pragma once
#include <memory>
namespace engine {

class Game;
class GameObject;

class State {
public:
	State(Game* game);

	virtual void update(float delta_time) = 0;
	virtual void render() = 0;

	Game* getGame();

	GameObject* getRoot();
	void setRoot(std::shared_ptr<GameObject>);

protected:
	Game* game;

	std::shared_ptr<GameObject> root;

	virtual void loadAssets() = 0;
	
};

}