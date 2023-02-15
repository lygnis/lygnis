#include "MGraphicsEngine.h"
#include <exception>
#include "DeviceContext.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
std::shared_ptr<MGraphicsEngine> MGraphicsEngine::_engine = nullptr;

MGraphicsEngine::MGraphicsEngine()
{
	try
	{
		_render_system = std::make_shared<RenderSystem>();
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

MaterialPtr MGraphicsEngine::CreateMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	MaterialPtr mat;
	mat = std::make_shared<Material>(vertex_shader_path, pixel_shader_path);
	return mat;
}

MaterialPtr MGraphicsEngine::CreateMaterial(const MaterialPtr& material)
{
	MaterialPtr mat;
	mat = std::make_shared<Material>(material);
	return mat;
}

void MGraphicsEngine::SetMaterial(const MaterialPtr& material, const bool wire_frame)
{
	// 레스터 라이스 컬링 모드 설정
	MGraphicsEngine::get()->getRenderSystem()->SetRaterizerState((material->_cullmode == CULL_MODE_FRONT), wire_frame);

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(material->_vertex_shader, material->_constant_buffer);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(material->_pixel_shader, material->_constant_buffer);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(material->_vertex_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(material->_pixel_shader);

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(material->_pixel_shader, &material->_vec_textures[0], material->_vec_textures.size());
}

SpritePtr MGraphicsEngine::CreateSprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	SpritePtr sprite;
	sprite = std::make_shared<Sprite>(vertex_shader_path, pixel_shader_path);
	return sprite;
}

SpritePtr MGraphicsEngine::CreateSprite(const SpritePtr& sprite)
{
	SpritePtr spr;
	spr = std::make_shared<Sprite>(sprite);
	return spr;
}

void MGraphicsEngine::SetSprite(const SpritePtr& sprite, const bool wire_frame, bool tex_anim, UINT anim_count)
{
	// 레스터 라이스 컬링 모드 설정
	MGraphicsEngine::get()->getRenderSystem()->SetRaterizerState(false, wire_frame);
	// 깊이 상태값 설정
	MGraphicsEngine::get()->getRenderSystem()->SetDepthStencilState();
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_vertex_shader, sprite->_constant_buffer);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_pixel_shader, sprite->_constant_buffer);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(sprite->_vertex_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(sprite->_pixel_shader);

	if (!sprite->_vec_textures.empty())
	{
		if(tex_anim)
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader, &sprite->_vec_textures[anim_count],1);
		else
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader, &sprite->_vec_textures[0], 1);
	}
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
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
