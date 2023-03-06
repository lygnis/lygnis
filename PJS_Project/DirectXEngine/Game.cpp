#include "Game.h"
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "Display.h"
Game::Game()
{
	graphics_engine_ = std::make_unique<MGraphicsEngine>();
	display_ = std::make_unique<Display>(this);
}

Game::~Game()
{
}

MGraphicsEngine* Game::GetGraphicsEngine()
{
	return graphics_engine_.get();
}
