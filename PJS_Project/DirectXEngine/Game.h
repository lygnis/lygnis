#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"

class Game
{
public:

private:
	std::unique_ptr<MGraphicsEngine> graphics_engine_;
	std::unique_ptr<Display> display_;
public:
	// 윈도우 초기화
	Game();
	virtual ~Game();
	MGraphicsEngine* GetGraphicsEngine();
public:
	void Run();
	bool is_running_ = true;
};

