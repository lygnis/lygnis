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
			image_data.GetImageCount(), image_data.GetMetadata(), _texture.GetAddressOf());

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

Texture::Texture(const TMath::Rect& size, Texture::Type type) : Resource(L"")
{
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = size.width;
	tex_desc.Height = size.height;
	// 텍스쳐 타입을 기반으로 한다
	if (type == NORMAL)
	{
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	}
	else if (type == RENDERTARGET)
	{
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	}
	else if (type == DEPTHSTECIL)
	{
		tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	}
		
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;

	HRESULT hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateTexture2D(&tex_desc, nullptr, (ID3D11Texture2D**)_texture.GetAddressOf());

	if (FAILED(hr))
	{
		throw std::exception("texture not create");
	}
	if (type == NORMAL || type == RENDERTARGET)
	{
		hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateShaderResourceView(_texture.Get(), NULL, &_srview);

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
	}
	else if (type == RENDERTARGET)
	{
		hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateRenderTargetView(_texture.Get(), NULL, render_target_view_.GetAddressOf());

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
	}
	else if (type == DEPTHSTECIL)
	{
		hr = MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateDepthStencilView(_texture.Get(), NULL, depth_stencil_view_.GetAddressOf());

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
	}
	t_type_ = type;
	rt_size_ = size;
}

Texture::~Texture()
{
	_srview->Release();
}

TMath::Rect Texture::GetSize()
{
	return rt_size_;
}

Texture::Type Texture::GetType()
{
	return t_type_;
}
