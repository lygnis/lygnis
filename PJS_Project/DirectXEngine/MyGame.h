#pragma once
#include "All.h"

class MyGame :public Game
{
public:
	MyGame();
	~MyGame();
protected:
	virtual void OnCreate();
	virtual void OnUpdate(float delta_time);
private:
	Entity* entity_ = nullptr;
	float elapsed_seconds = 0.0f;

	float rotation_ = 0.0f;
};

