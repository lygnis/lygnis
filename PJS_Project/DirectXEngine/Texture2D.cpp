#include "Texture2D.h"
#include <DirectXTex.h>
#include "MGraphicsEngine.h"
#include "RenderSystem.h"

Texture2D::Texture2D(const wchar_t* full_path, RenderSystem* system) : r_system_(system)
{
	DirectX::ScratchImage image_data;
	// png jpg 등 다 읽을 수 있다.
	HRESULT hr = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

	if (SUCCEEDED(hr))
	{
		// 파일 읽으면 텍스쳐 생성
		hr = DirectX::CreateTexture(r_system_->_d3d_Device.Get(), image_data.GetImages(),
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

		hr = r_system_->_d3d_Device.Get()->CreateSamplerState(&sampler_desc, &_sampler_state);
		if (FAILED(hr))
			assert(false);

		hr = r_system_->_d3d_Device.Get()->CreateShaderResourceView(_texture.Get(), &desc, &_srview);
		if (FAILED(hr))
			assert(false);
	}
	else
	{
		assert(false);
		throw std::exception("Texture not created");
	}
}

Texture2D::Texture2D(const TMath::Rect& size, Texture2D::Type type, RenderSystem* system) : r_system_(system)
{
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = size.width;
	tex_desc.Height = size.height;
	// 텍스쳐 타입을 기반으로 한다
	if (type == Texture2D::Type::NORMAL)
	{
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	}
	else if (type == Texture2D::Type::RENDERTARGET)
	{
		tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	}
	else if (type == Texture2D::Type::DEPTHSTECIL)
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

	HRESULT hr = r_system_->_d3d_Device.Get()->CreateTexture2D(&tex_desc, nullptr, (ID3D11Texture2D**)_texture.GetAddressOf());

	if (FAILED(hr))
	{
		throw std::exception("texture not create");
	}
	if (type == Texture2D::Type::NORMAL || type == Texture2D::Type::RENDERTARGET)
	{
	}
	if (type == Texture2D::Type::RENDERTARGET)
	{
		hr = r_system_->_d3d_Device.Get()->CreateShaderResourceView(_texture.Get(), NULL, &_srview);

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
		hr = r_system_->_d3d_Device.Get()->CreateRenderTargetView(_texture.Get(), NULL, render_target_view_.GetAddressOf());

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
	}
	else if (type == Texture2D::Type::DEPTHSTECIL)
	{
		hr = r_system_->_d3d_Device.Get()->CreateDepthStencilView(_texture.Get(), NULL, depth_stencil_view_.GetAddressOf());

		if (FAILED(hr))
		{
			assert(false);
			throw std::exception("texture not create successfully");
		}
	}
	t_type_ = type;
	rt_size_ = size;
}

TMath::Rect Texture2D::GetSize()
{
	return rt_size_;
}

