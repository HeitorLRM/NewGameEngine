#pragma once

#include "CameraFeed.hpp"
#include "Game.hpp"
#include "Object2D.hpp"
#include "Ref.hpp"
#include "Transform2D.hpp"

namespace engine {

class Camera2D : public Object2D {
public:
	virtual const std::string& getResourceType() const override;

	void load() override;
	void unload() override;
	void update(float) override;

	const Transform2D& getInverseGlobal();

public:
	Ref<CameraFeed> feed = Game::window_feed;
	bool is_active = true;

private:
	void mark_global_transform_dirty() override;

	Transform2D inv_global;
	bool is_inv_global_dirty = true;
};

}
