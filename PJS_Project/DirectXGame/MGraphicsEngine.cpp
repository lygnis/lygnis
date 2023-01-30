#include "MGraphicsEngine.h"
#include <exception>

std::shared_ptr<MGraphicsEngine> MGraphicsEngine::_engine = nullptr;

MGraphicsEngine::MGraphicsEngine()
{
	try
	{
		_render_system = std::make_unique<RenderSystem>();
	}
	catch (...) { throw std::exception("GrapicsEngine not create successfully"); }
	
	try
	{
		_tex_manager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not create successfully"); }

	try
	{
		_mesh_manger = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not create successfully"); }

	// 쉐이더 컴파일
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	_render_system->CompileVertexShader(L"VertexMesh.hlsl", "mainvs", &shader_byte_code, &size_shader);
	::memcpy(_mesh_layout_byte_code, shader_byte_code, size_shader);
	_mesh_layout_size = size_shader;

}

MGraphicsEngine::~MGraphicsEngine()
{
	_tex_manager->Release();
	delete _tex_manager;
	delete _mesh_manger;
}

RenderSystem* MGraphicsEngine::getRenderSystem()
{
	return _render_system.get();
}

TextureManager* MGraphicsEngine::getTextureManager()
{
	return _tex_manager;
}

MeshManager* MGraphicsEngine::getMeshManager()
{
	return _mesh_manger;
}

void MGraphicsEngine::GetVertexMeshLayoutShader(void** byte_code, size_t* size)
{
	*byte_code = _mesh_layout_byte_code;
	*size = _mesh_layout_size;
}


MGraphicsEngine* MGraphicsEngine::get()
{
	return _engine.get();
}

void MGraphicsEngine::Create()
{
	if (MGraphicsEngine::_engine) throw std::exception("Graphics Engine already created");
	MGraphicsEngine::_engine = std::make_shared<MGraphicsEngine>();
}

void MGraphicsEngine::Release()
{
	if (!MGraphicsEngine::_engine) return;

}
