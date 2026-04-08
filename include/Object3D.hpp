#pragma once

#include "GameObject.hpp"
#include "Transform3D.hpp"

namespace engine {

class Object3D : public GameObject {
public:
	virtual const std::string& getResourceType() const override;

	Transform3D& getTransform();
	const Transform3D& getTransform() const;
	const Transform3D& getGlobalTransform();
	void setParent(GameObject *) final;

protected:
	virtual void mark_global_transform_dirty();

private:
	Transform3D transform;
	Transform3D global_transform;
	bool is_global_transform_dirty = true;
};

}

