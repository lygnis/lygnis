#pragma once
//#include <d3d11.h>
#include "MStd.h"
//#include "RenderSystem.h"
//#include "TextureManager.h"
//#include "MeshManager.h"
//#include "Material.h"

class MGraphicsEngine
{
public:
	MGraphicsEngine();
	~MGraphicsEngine();
public:
	RenderSystem* getRenderSystem();
private:
	std::unique_ptr<RenderSystem> _render_system;

};

