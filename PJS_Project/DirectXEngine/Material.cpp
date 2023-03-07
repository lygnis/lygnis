#include "Material.h"
#include "MGraphicsEngine.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "Game.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "ConstantBuffer.h"
#include <exception>
#include "Texture.h"
Material::Material(const wchar_t* path, ResourceManager* manager) :Resource(path,manager)
{
	auto rsys = manager->GetGame()->GetGraphicsEngine()->getRenderSystem();

	_vertex_shader = rsys->CreateVertexShader(path, "mainvs");
	if (!_vertex_shader)
		throw std::runtime_error("Material not created successfully");


	_pixel_shader = rsys->CreatePixelShader(path, "mainps");
	if(!_pixel_shader)
		throw std::runtime_error("Material not created successfully");

}

Material::Material(const MaterialPtr& material, ResourceManager* manager) : Resource(L"", manager)
{
	_vertex_shader = material->_vertex_shader;
	_pixel_shader = material->_pixel_shader;
}



void Material::AddTexture(const TexturePtr& texture)
{
	_vec_textures.push_back(texture->texture_);
}

void Material::RemoveTexture(UINT index)
{
	if (index >= this->_vec_textures.size())
		return;
	_vec_textures.erase(_vec_textures.begin() + index);
}

void Material::SetData(void* data, UINT size)
{
	auto rsys = manager_->GetGame()->GetGraphicsEngine()->getRenderSystem();

	if(!_constant_buffer)
		_constant_buffer = rsys->CreateConstantBuffer(data, size);
	else
	{
		_constant_buffer->Update(rsys->getImmediateDeviceContext(), data);
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
