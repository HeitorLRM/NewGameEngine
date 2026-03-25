// TODO ownership: Heitor

#pragma once
#include "GameObject.hpp"
#include "Ref.hpp"
namespace engine {

class Stage : public Resource {
public:
	Stage() = default;

	virtual void load() override;
	virtual void unload() override;
	virtual void update(float delta_time);
	virtual void render();

	GameObject* getRoot();
	void setRoot(Ref<GameObject>);

protected:
	Ref<GameObject> root;

};

}