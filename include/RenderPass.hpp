#pragma once

#include <queue>
#include "CameraFeed.hpp"
#include "Ref.hpp"

namespace engine {

class Camera2D;
class Camera3D;
class GameObject;

class RenderPass {
public:
	void queue(GameObject* obj);
	void flush();

public:
	Camera2D* active_camera2D = nullptr;
	Camera3D* active_camera3D = nullptr;
	Ref<CameraFeed> getFeed();

	struct QueueEntry {
		bool operator<(const QueueEntry& other) const {
			return priority < other.priority;
		}

		float priority;
		GameObject* obj;
	};

private:
	std::priority_queue<QueueEntry> render_queue;
};


}
