// TODO ownership: Heitor

#pragma once

#include "RenderPass.hpp"
#include "Ref.hpp"
#include <cstdint>
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
	static void registerPass(Camera2D*);
	static void registerPass(Camera3D*);
	static RenderPass* getRenderPass();

	static void enqueueKill(Ref<GameObject>);

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
	static std::vector<RenderPass> render_passes;
	static std::queue<Ref<GameObject>> kill_queue;
	static bool quit_requested;
	static uint64_t lastTicks;
	static Ref<GameObject> root;
};

}
