#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"

class Game
{
public:

private:
	std::unique_ptr<MGraphicsEngine> graphics_engine_;
	std::unique_ptr<Display> display_;
	std::unique_ptr<ResourceManager> resource_manager_;
	MeshPtr mesh_;
	MaterialPtr material_;
protected:
	virtual void OnCreate() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnQuit() {}
private:
	void OnInternalUpdate();
public:
	// 윈도우 초기화
	Game();
	virtual ~Game();
	MGraphicsEngine* GetGraphicsEngine();
public:
	void Run();
	void Quit();
	bool is_running_ = true;

	friend class MGraphicsEngine;
};

