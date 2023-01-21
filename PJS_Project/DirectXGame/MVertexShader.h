#pragma once
#include "MStd.h"

class MGraphicsEngine;
class DeviceContext;

class MVertexShader
{
public:
	MVertexShader() {};
	~MVertexShader() {};
	bool Release() {};
private:
	bool Init(const void* shader_byte_code, size_t byte_code_size);
private:
	ComPtr<ID3D11VertexShader> _vsShader;
private:
	friend class MGraphicsEngine;
	friend class DeviceContext;
};

