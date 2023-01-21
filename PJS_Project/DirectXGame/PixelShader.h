#pragma once
#include "MStd.h"

class MGraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader() {};
	~PixelShader() {};
	bool Release() {};
private:
	bool Init(const void* shader_byte_code, size_t byte_code_size);
private:
	ComPtr<ID3D11PixelShader> _psShader;
private:
	friend class MGraphicsEngine;
	friend class DeviceContext;
};

