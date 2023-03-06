#include "Display.h"
#include "Game.h"
#include "MGraphicsEngine.h"
#include "RenderSystem.h"
Display::Display(Game* game) : game_(game)
{
	auto size = GetClientSize();
	swap_chain_ = game->GetGraphicsEngine()->getRenderSystem()->CreateSwapChain(static_cast<HWND>(_hwnd), size.width, size.height);
}

Display::~Display()
{
}
