// TODO ownership: Heitor

#pragma once

#include <memory>

namespace engine {

class State;
class AppIO;

class Game {
public:
	Game();

	void run();
	void requestQuit();
	
	std::weak_ptr<State> getState();
	std::weak_ptr<AppIO> getInterface();

protected:
	void setState(std::shared_ptr<State>);
	void setInterface(std::shared_ptr<AppIO>);

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void mainLoop();
	virtual bool shouldQuit();

private:
	bool quit_requested;
	std::shared_ptr<State> state;
	std::shared_ptr<AppIO> interface;
};

}
