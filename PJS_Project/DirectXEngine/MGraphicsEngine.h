#pragma once
//#include <d3d11.h>
#include "MStd.h"
//#include "RenderSystem.h"
//#include "TextureManager.h"
//#include "MeshManager.h"
//#include "Material.h"


struct MeshData
{
	MeshPtr mesh;
	MaterialPtr material;
};

class MGraphicsEngine
{
public:
	MGraphicsEngine(Game* game);
	~MGraphicsEngine();
public:
	RenderSystem* getRenderSystem();

	void Update(const MeshData& data);
private:
	std::unique_ptr<RenderSystem> _render_system;
	Game* game_ = nullptr;
};

