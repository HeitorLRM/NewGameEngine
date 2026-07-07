#include "Camera2D.hpp"
#include "Camera3D.hpp"
#include "RenderPass.hpp"
#include "GameObject.hpp"
#include "SDL_AppIO.hpp"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

using namespace engine;

void RenderPass::queue(GameObject* obj) {
	QueueEntry entry;
	if (active_camera2D)
		entry = active_camera2D->makeEntry(obj);
	else if (active_camera3D)
		entry = active_camera3D->makeEntry(obj);

	if (entry.obj == nullptr)
		return;

	render_queue.push(entry);
}

Ref<CameraFeed> RenderPass::getFeed() {
    Ref<CameraFeed> feed;
	if (active_camera2D)
		feed = active_camera2D->feed;
	else if (active_camera3D)
		feed = active_camera3D->feed;
	return feed;
}

void RenderPass::flush() {
    auto feed = getFeed();
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
