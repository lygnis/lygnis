#include "Game.h"
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "Display.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Input.h"
#include "World.h"

void Game::OnDisplaySize(const TMath::Rect& size)
{
	OnInternalUpdate();
}
void Game::OnInternalUpdate()
{
	// deltatime
	auto current_time = std::chrono::system_clock::now();
	auto elaped_second = std::chrono::duration<double>();
	if (previous_time.time_since_epoch().count())
	{
		elaped_second = current_time - previous_time;
	}
	previous_time = current_time;
	auto deltaTime = (float)elaped_second.count();


	input_->Frame();
	OnUpdate(deltaTime);
	world_->Update(deltaTime);
	graphics_engine_->Update();
}
Game::Game()
{
	input_ = std::make_unique<Input>();
	input_->Init();
	graphics_engine_ = std::make_unique<MGraphicsEngine>(this);
	display_ = std::make_unique<Display>(this);
	resource_manager_ = std::make_unique<ResourceManager>(this);
	world_ = std::make_unique<World>(this);


}

Game::~Game()
{
}

World* Game::GetWorld()
{
	return world_.get();
}

MGraphicsEngine* Game::GetGraphicsEngine()
{
	return graphics_engine_.get();
}
ResourceManager* Game::GetResourceManager()
{
	return resource_manager_.get();
}
void Game::Quit()
{
	is_running_ = false;
}
