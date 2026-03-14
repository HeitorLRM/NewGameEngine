// TODO ownership: Heitor

#pragma once

#include "AppIO.hpp"

#include <memory>
#include <vector>

namespace engine {

class AppIO;
class Stage;

class Game {
public:
	Game();

	void run();
	void requestQuit();
	
	std::shared_ptr<AppIO> getInterface();

protected:
	void loadStage(Ref<Stage>);
	void unloadStage(Ref<Stage>);
	void setInterface(std::shared_ptr<AppIO>);

	virtual void init() = 0;
	virtual void close() = 0;

	virtual void mainLoop();
	virtual bool shouldQuit();

	const std::vector<Ref<Stage>>& getLoadedStages();

private:
	bool quit_requested;
	std::vector<Ref<Stage>> loaded_stages;
	std::shared_ptr<AppIO> interface;
};

}
