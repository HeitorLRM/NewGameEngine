#pragma once

#include <queue>

namespace engine {

class Camera;
class GameObject;

class RenderPass {
public:
	void queue(GameObject* obj);
	void flush();

public:
	Camera* active_camera;

private:
	struct QueueEntry {
		bool operator<(const QueueEntry& other) const {
			return priority < other.priority;
		}

		float priority;
		GameObject* obj;
	};

	std::priority_queue<QueueEntry> render_queue;
};


}
