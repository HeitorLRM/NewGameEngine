// TODO ownership: Heitor

#pragma once

#include <memory>

namespace engine {

class Stage;
class AppIO;

class Game {
public:
	Game();

	void run();
	void requestQuit();
	
	std::weak_ptr<Stage> getStage();
	std::weak_ptr<AppIO> getInterface();

protected:
	void setStage(std::shared_ptr<Stage>);
	void setInterface(std::shared_ptr<AppIO>);

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void mainLoop();
	virtual bool shouldQuit();

private:
	bool quit_requested;
	std::shared_ptr<Stage> stage;
	std::shared_ptr<AppIO> interface;
};

}
