#pragma once
#include "Resource.h"
#include"MStd.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();
private:
	ComPtr<ID3D11Resource> _texture = nullptr;
	ID3D11ShaderResourceView* _srview;
	ID3D11SamplerState* _sampler_state;
	friend class DeviceContext;
};

