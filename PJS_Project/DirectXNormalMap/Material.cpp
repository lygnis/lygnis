#include "Material.h"
#include "MGraphicsEngine.h"
#include <exception>
Material::Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	MGraphicsEngine::get()->getRenderSystem()->CompileVertexShader(vertex_shader_path, "mainvs", &shader_byte_code, &size_shader);
	_vertex_shader = std::move(MGraphicsEngine::get()->getRenderSystem()->CreateVertexShader(shader_byte_code, size_shader));

	//_vb = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	if (!_vertex_shader)
		throw std::runtime_error("Material not created successfully");


	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps", &shader_byte_code, &size_shader);
	_pixel_shader = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));

	if(!_pixel_shader)
		throw std::runtime_error("Material not created successfully");

}

Material::Material(const MaterialPtr& material)
{
	_vertex_shader = material->_vertex_shader;
	_pixel_shader = material->_pixel_shader;
}

Material::~Material()
{

}

void Material::AddTexture(const TexturePtr& texture)
{
	_vec_textures.push_back(texture);
}

void Material::RemoveTexture(UINT index)
{
	if (index >= this->_vec_textures.size())
		return;
	_vec_textures.erase(_vec_textures.begin() + index);
}

void Material::SetData(void* data, UINT size)
{
	if(!_constant_buffer)
		_constant_buffer = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(data, size);
	else
	{
		_constant_buffer->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
	}
}

void Material::SetCullMode(CULL_MODE mode)
{
	_cullmode = mode;
}

CULL_MODE Material::GetCullMode()
{
	return _cullmode;
}
