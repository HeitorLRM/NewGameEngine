// TDOO ownership: Heitor

#include "Camera2D.hpp"

#include "Game.hpp"
#include "RenderPass.hpp"
#include "AppIO.hpp"
#include "SDL_AppIO.hpp"
#include "GameObject.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <queue>
#include <vector>

using namespace engine;

using std::queue;
using std::vector;

Ref<CameraFeed> Game::window_feed;
queue<Ref<GameObject>> Game::kill_queue;
vector<RenderPass> Game::render_passes;
bool Game::quit_requested = false;
Ref<GameObject> Game::root;
uint64_t Game::lastTicks = 0;


void Game::requestQuit() {
	quit_requested = true;
}

bool Game::shouldQuit() {
	return (
		AppIO::shouldClose() ||
		quit_requested
	);
}

void Game::loadRoot(Ref<GameObject> r) {
	if (root)
		unloadRoot();

	root = r;

	root.load_ref();
}

void Game::unloadRoot() {
	root.unload_ref();
}

Ref<GameObject> Game::getRoot() {
	return root;
}

void Game::registerPass(Camera2D* c) {
	RenderPass pass;
	pass.active_camera2D = c;
	render_passes.push_back(pass);
}

void Game::registerPass(Camera3D* c) {
	RenderPass pass;
	pass.active_camera3D = c;
	render_passes.push_back(pass);
}

RenderPass* Game::getRenderPass() {
	if (render_passes.empty())
		return nullptr;

	return &render_passes.back();
}

void Game::run() {
	init();

	while (!shouldQuit()) {
		mainLoop();
	}

	close();
}

void Game::enqueueKill(Ref<GameObject> obj) {
    kill_queue.push(obj);
}

void Game::mainLoop() {
	AppIO::update();

	uint64_t nowTicks = SDL_GetTicksNS();
	float deltaTime = (nowTicks-lastTicks)/1e9;
	lastTicks = nowTicks;

	auto cur_root = root;
	if (cur_root) {
		cur_root->update(deltaTime);
	}

	reverse(render_passes.begin(), render_passes.end());

	// just clear everything, regardless of order
	for (auto &pass : render_passes) {
	 	pass.getFeed()->clear();
	}

	// render back to front
	while (auto pass = getRenderPass()) {
		cur_root->preRender();
		pass->flush();
		render_passes.pop_back();
	}
	render_passes.clear();

	while (!kill_queue.empty()) {
	    auto obj = kill_queue.front();
		kill_queue.pop();
		if (obj->getParent()) {
		    obj->getParent()->removeChild(obj.get());
		}
	}

	AppIO::render();
}

void Game::init() {
	AppIO::init();

	window_feed = Ref(new CameraFeed);
	window_feed->screen_area = {Vec2::ZERO, AppIO::SDL::window_dimensions};
	window_feed.load_ref();

	if (init_callback)
		init_callback();
}

void Game::close() {
	if (close_callback)
		close_callback();

	window_feed.unload_ref();

	unloadRoot();
	AppIO::close();
}
