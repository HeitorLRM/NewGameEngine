// TODO ownership: Heitor

#pragma once

#include "RenderPass.hpp"
#include "Ref.hpp"
namespace engine {

class GameObject;
class CameraFeed;

class Game {
public:
	Game() = delete;

	static void run();
	static void requestQuit();
	
	static void loadRoot(Ref<GameObject>);
	static void unloadRoot();
	static Ref<GameObject> getRoot();
	static void registerPass(Camera*);
	static void registerPass(Camera3D*);
	static RenderPass* getRenderPass();

private:
	static void init();
	static void close();

	static void mainLoop();
	static bool shouldQuit();
	
public:
	static void (*init_callback)();
	static void (*close_callback)();

	static Ref<CameraFeed> window_feed;

private:
	static std::queue<RenderPass> render_passes;
	static bool quit_requested;
	static Ref<GameObject> root;
};

}
