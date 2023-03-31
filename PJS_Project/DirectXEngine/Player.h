#pragma once
#include "All.h"
class Player : public Entity
{
public:
	Player();
	~Player();
protected:
	virtual void OnCreate();
	virtual void OnUpdate(float delta_time);
private:
	Entity* entity_ = nullptr;
	float elapsed_seconds = 0.0f;
};

