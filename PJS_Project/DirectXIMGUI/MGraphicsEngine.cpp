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
	try
	{
		obj_manager_ = std::make_shared<ObjectManager>();
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

std::shared_ptr<ObjectManager> MGraphicsEngine::GetObjectManager()
{
	return obj_manager_;
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

void MGraphicsEngine::SetState(const bool wire_frame, bool on_z_buffer, bool z_buffer_write, bool blend_state)
{
	// 레스터 라이스 컬링 모드 설정
	MGraphicsEngine::get()->getRenderSystem()->SetRaterizerState(false, wire_frame);
	// 깊이 상태값 설정
	MGraphicsEngine::get()->getRenderSystem()->SetDepthStencilState(on_z_buffer, z_buffer_write);
	// 블렌드 스테이트 설정
	MGraphicsEngine::get()->getRenderSystem()->SetBlendState(blend_state);
}

void MGraphicsEngine::SetSprite(const SpritePtr& sprite, bool tex_anim, int anim_count)
{
	//UINT tex_index = sprite->texture_index_;
	
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_vertex_shader, sprite->_constant_buffer);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_pixel_shader, sprite->_constant_buffer);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(sprite->_vertex_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(sprite->_pixel_shader);

	if (!sprite->list_textures_.empty())
	{
		if(tex_anim )
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader, &sprite->list_textures_[anim_count],1);
		else
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader, &sprite->list_textures_[anim_count], 1);
	}
}

void MGraphicsEngine::SetTesttingSprite(const SpritePtr& sprite, bool tex_anim, int anim_count)
{
	//UINT tex_index = sprite->texture_index_;

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_vertex_shader, sprite->_constant_buffer);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_pixel_shader_discard, sprite->_constant_buffer);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(sprite->_vertex_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(sprite->_pixel_shader_discard);

	if (!sprite->list_textures_.empty())
	{
		if (tex_anim)
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader_discard, &sprite->list_textures_[anim_count], 1);
		else
			MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader_discard, &sprite->list_textures_[anim_count], 1);
	}
}

void MGraphicsEngine::SetButton(const ButtonPtr& sprite, ButtonState state)
{
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_vertex_shader, sprite->_constant_buffer);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(sprite->_pixel_shader, sprite->_constant_buffer);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(sprite->_vertex_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(sprite->_pixel_shader);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(sprite->_pixel_shader, &sprite->list_textures_[state], 1);
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

void MGraphicsEngine::SaveToJson(const std::string& filepath)
{

}

void MGraphicsEngine::LoadToJson(const std::string& filepath)
{

}
