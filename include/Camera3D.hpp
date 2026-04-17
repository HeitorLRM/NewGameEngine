#pragma once

#include "Game.hpp"
#include "Math.hpp"
#include "Matrix4.hpp"
#include "Object3D.hpp"
#include "Ref.hpp"
#include "Transform3D.hpp"

class SDL_Texture;

namespace engine {

class Camera3D : public Object3D {
public:
	virtual const std::string& getResourceType() const override;

	void load() override;
	void unload() override;
	void update(float) override;

	const Transform3D& getInverseGlobal();
	Matrix4 getProjectionMatrix() const;

public:
	Ref<CameraFeed> feed = Game::window_feed;
	bool is_active = true;
	float near = 0.1;
	float far = 10000.0;
	float fov = PI/2.0;

private:
	void mark_global_transform_dirty() override;

	Transform3D inv_global;
	bool is_inv_global_dirty = true;
};

}
