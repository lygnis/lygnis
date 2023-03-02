#pragma once
#include "MStd.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size ,RenderSystem* system);
	~PixelShader() {};
private:
	ComPtr<ID3D11PixelShader> _psShader;
	RenderSystem* _system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};

