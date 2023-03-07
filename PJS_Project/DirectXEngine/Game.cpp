#include "Game.h"
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "Display.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
void Game::OnInternalUpdate()
{
	graphics_engine_->Update({mesh_, material_});
}
Game::Game()
{
	graphics_engine_ = std::make_unique<MGraphicsEngine>(this);
	display_ = std::make_unique<Display>(this);
	resource_manager_ = std::make_unique<ResourceManager>(this);

	mesh_ = resource_manager_->CreateResourceFromFile<Mesh>(L"../../data/Meshes/house.obj");
	auto tex = resource_manager_->CreateResourceFromFile<Texture>(L"../../data/Textures/wood.jpg");

	material_ = resource_manager_->CreateResourceFromFile<Material>(L"MyMaterial.hlsl");
	material_->AddTexture(tex);
}

Game::~Game()
{
}

MGraphicsEngine* Game::GetGraphicsEngine()
{
	return graphics_engine_.get();
}
void Game::Quit()
{
	is_running_ = false;
}
