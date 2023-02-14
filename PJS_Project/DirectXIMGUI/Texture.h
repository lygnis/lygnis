#pragma once
#include "Resource.h"
#include"MStd.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();
	D3D11_TEXTURE2D_DESC GetImageDesc();
private:
	D3D11_TEXTURE2D_DESC   tex_desc_;
	ComPtr<ID3D11Texture2D> _texture = nullptr;
	ID3D11ShaderResourceView* _srview;
	ID3D11SamplerState* _sampler_state;
	friend class DeviceContext;
};

