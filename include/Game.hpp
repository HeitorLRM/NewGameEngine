// TODO ownership: Heitor

#pragma once

#include <memory>
#include <set>

namespace engine {

class Stage;
class AppIO;

class Game {
public:
	Game();

	void run();
	void requestQuit();
	
	std::weak_ptr<AppIO> getInterface();

protected:
	void loadStage(std::shared_ptr<Stage>);
	void unloadStage(std::shared_ptr<Stage>);
	void setInterface(std::shared_ptr<AppIO>);

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void mainLoop();
	virtual bool shouldQuit();

	const std::set<std::shared_ptr<Stage>>& getLoadedStages();

private:
	bool quit_requested;
	std::set<std::shared_ptr<Stage>> loaded_stages;
	std::shared_ptr<AppIO> interface;
};

}
