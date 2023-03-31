#pragma once
//#include <d3d11.h>
#include "MStd.h"
#include <set>


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

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	void Update();
private:
	std::unique_ptr<RenderSystem> _render_system;
	Game* game_ = nullptr;

	std::set<MeshComponent*> meshes_;
	std::set<CameraComponent*> cameras_;
};

