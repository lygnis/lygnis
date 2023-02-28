#pragma once
#include "MStd.h"

class MVertexShader
{
public:
	MVertexShader(const void* shader_byte_code, size_t byte_code_size ,RenderSystem* system);
	~MVertexShader() {};
private:
	ComPtr<ID3D11VertexShader> _vsShader;
	RenderSystem* _system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};

