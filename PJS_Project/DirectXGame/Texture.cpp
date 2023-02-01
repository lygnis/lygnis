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

		MGraphicsEngine::get()->getRenderSystem()->_d3d_Device->CreateShaderResourceView(_texture.Get(), &desc, &_srview);
	}
	else
	{
		throw std::exception("Texture not created");
	}
}

Texture::~Texture()
{
	_srview->Release();
}
