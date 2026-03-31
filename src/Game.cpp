// TDOO ownership: Heitor

#include "Game.hpp"
#include "Camera.hpp"
#include "RenderPass.hpp"
#include "AppIO.hpp"
#include "SDL_AppIO.hpp"
#include "GameObject.hpp"

#include <queue>

using namespace engine;

using std::queue;

Ref<CameraFeed> Game::window_feed;
queue<RenderPass> Game::render_passes;
bool Game::quit_requested = false;
Ref<GameObject> Game::root;


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

void Game::registerPass(Camera* c) {
	RenderPass pass;
	pass.active_camera = c;
	render_passes.push(pass);
}

RenderPass* Game::getRenderPass() {
	if (render_passes.empty())
		return nullptr;

	return &render_passes.front();
}

void Game::run() {
	init();

	while (!shouldQuit()) {
		mainLoop();
	}

	close();
}

void Game::mainLoop() {
	AppIO::update();

	if (root) {
		root->update(1.0/30.0);
	}

	while(auto pass = getRenderPass()) {
		root->pre_render();
		pass->flush();
		render_passes.pop();
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

