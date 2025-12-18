// TODO ownership: Heitor

#pragma once

#include <memory>

namespace engine {

class State;
class UserInterface;

class Game {
public:
	Game();

	void run();
	void requestQuit();
	
	std::weak_ptr<State> getState();
	UserInterface* getInterface();

protected:
	void setState(std::shared_ptr<State>);
	void setInterface(UserInterface*);

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void mainLoop();
	virtual bool shouldQuit();

private:
	bool quit_requested;
	std::shared_ptr<State> state;
	UserInterface* interface;
};

}
