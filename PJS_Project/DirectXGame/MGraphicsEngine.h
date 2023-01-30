#pragma once
#include <d3d11.h>
#include "MStd.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"
class MGraphicsEngine
{
public:
	MGraphicsEngine();
	~MGraphicsEngine();
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	void GetVertexMeshLayoutShader(void** byte_code, size_t* size);
public:
	// ΩÃ±€≈Ê
	static MGraphicsEngine* get();
	static void				Create();
	static void				Release();
private:
	std::unique_ptr<RenderSystem> _render_system;
	TextureManager* _tex_manager = nullptr;
	MeshManager* _mesh_manger = nullptr;

	static std::shared_ptr<MGraphicsEngine> _engine;

	unsigned char _mesh_layout_byte_code[1024];
	size_t _mesh_layout_size = 0;
};

