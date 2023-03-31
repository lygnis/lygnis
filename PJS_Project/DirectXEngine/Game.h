#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"
#include <chrono>
class Game
{
public:

private:
	std::unique_ptr<Input> input_;
	std::unique_ptr<MGraphicsEngine> graphics_engine_;
	std::unique_ptr<Display> display_;
	std::unique_ptr<ResourceManager> resource_manager_;
	std::unique_ptr<World> world_;
protected:
	virtual void OnCreate() {}
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnQuit() {}

private:
	void OnDisplaySize(const TMath::Rect& size);
	void OnInternalUpdate();
public:
	// 윈도우 초기화
	Game();
	virtual ~Game();
	World* GetWorld();
	MGraphicsEngine* GetGraphicsEngine();
	ResourceManager* GetResourceManager();
public:
	void Run();
	void Quit();
	bool is_running_ = true;
	std::chrono::system_clock::time_point previous_time;

	friend class MGraphicsEngine;
	friend class Display;

};

