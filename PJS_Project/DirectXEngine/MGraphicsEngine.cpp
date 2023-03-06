#include "MGraphicsEngine.h"
#include "DeviceContext.h"
#include "RenderSystem.h"

MGraphicsEngine::MGraphicsEngine()
{
	_render_system = std::make_unique<RenderSystem>();
}

MGraphicsEngine::~MGraphicsEngine()
{
}

RenderSystem* MGraphicsEngine::getRenderSystem()
{
	return _render_system.get();
}


