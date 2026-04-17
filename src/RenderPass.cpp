#include "Camera.hpp"
#include "Camera3D.hpp"
#include "RenderPass.hpp"
#include "GameObject.hpp"
#include "SDL_AppIO.hpp"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "Sprite.hpp"
#include "Sprite3D.hpp"

using namespace engine;

void RenderPass::queue(GameObject* obj) {
	QueueEntry entry;
	entry.obj = obj;

	if (auto obj_sprite = dynamic_cast<Sprite*>(obj))
		entry.priority = obj_sprite->z_index;
	else if (auto obj_sprite3D = dynamic_cast<Sprite3D*>(obj))
		entry.priority = obj_sprite3D->z_index;

	render_queue.push(entry);
}

void RenderPass::flush() {
	Ref<CameraFeed> feed;
	if (active_camera2D)
		feed = active_camera2D->feed;
	else if (active_camera3D)
		feed = active_camera3D->feed;
	if (!feed) return;

	SDL_SetRenderTarget(AppIO::SDL::renderer, feed->output);

	SDL_SetRenderDrawColor(
		AppIO::SDL::renderer, 
		feed->fill_color.r * 255, 
		feed->fill_color.g * 255, 
		feed->fill_color.b * 255, 
		feed->fill_color.a * 255
	);
	SDL_RenderClear(AppIO::SDL::renderer);


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

