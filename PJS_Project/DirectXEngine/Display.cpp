#include "Display.h"
#include "Game.h"
#include "MGraphicsEngine.h"
#include "RenderSystem.h"
#include "MSwapChain.h"
Display::Display(Game* game) : game_(game)
{
	auto size = GetClientSize();
	swap_chain_ = game->GetGraphicsEngine()->getRenderSystem()->CreateSwapChain(static_cast<HWND>(_hwnd), size.width, size.height);
}

Display::~Display()
{
}

void Display::OnSize(const TMath::Rect& size)
{
	swap_chain_->Resize(size.width, size.height);

	game_->OnDisplaySize(size);
}
