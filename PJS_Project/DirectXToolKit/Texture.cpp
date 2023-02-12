#include "Texture.h"
#include <DirectXTex.h>
#include "MGraphicsEngine.h"

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	DirectX::ScratchImage image_data;
	// png jpg 등 다 읽을 수 있다.
	HRESULT hr = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

	if (SUCCEEDED(hr))
	{
		// 파일 읽으면 텍스쳐 생성
		hr = DirectX::CreateTexture(MGraphicsEngine::get()->getRenderSystem()->_d3d_Device.Get(), image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), (ID3D11Resource**)_texture.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		D3D11_SAMPLER_DESC sampler_desc = {};
		// 텍스쳐 매핑
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = image_data.GetMetadata().mipLevels;

		hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateSamplerState(&sampler_desc, &_sampler_state);
		if (FAILED(hr))
			assert(false);

		hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateShaderResourceView(_texture.Get(), &desc, &_srview);
		if (FAILED(hr))
			assert(false);
	}
	else
	{
		assert(false);
		throw std::exception("Texture not created");
	}
}

Texture::~Texture()
{
	_srview->Release();
}

D3D11_TEXTURE2D_DESC Texture::GetImageDesc()
{
	_texture->GetDesc(&tex_desc_);
	return tex_desc_;
}
