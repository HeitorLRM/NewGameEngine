#include "Camera.hpp"
#include "RenderPass.hpp"
#include "GameObject.hpp"
#include "SDL_AppIO.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "Sprite.hpp"

using namespace engine;

void RenderPass::queue(GameObject* obj) {
	QueueEntry entry;
	entry.obj = obj;

	if (auto obj_sprite = dynamic_cast<Sprite*>(obj))
		entry.priority = obj_sprite->z_index;

	render_queue.push(entry);
}

void RenderPass::flush() {
	if (!active_camera) return;

	auto feed = active_camera->feed;
	if (!feed) return;

	SDL_SetRenderTarget(AppIO::SDL::renderer, feed->output);
	while (!render_queue.empty()) {	
		auto obj = render_queue.top().obj;
		render_queue.pop();
		obj->render();
	}

	SDL_SetRenderTarget(AppIO::SDL::renderer, nullptr);
	auto& screen_area = feed->screen_area;
	SDL_FRect clip{
		0,
		0, 
		screen_area.w, 
		screen_area.h
	};
	SDL_FRect dst{
		screen_area.x,
		screen_area.y,
		screen_area.w,
		screen_area.h
	};

	SDL_RenderTexture(
		AppIO::SDL::renderer, 
		feed->output, 
		&clip,
		&dst
	);
}

