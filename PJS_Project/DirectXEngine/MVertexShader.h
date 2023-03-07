#pragma once
#include "MStd.h"

class MVertexShader
{
public:
	MVertexShader(const wchar_t* full_path ,const char* entry_point, RenderSystem* system);
	~MVertexShader() {};
private:
	ComPtr<ID3D11VertexShader> _vsShader;
	RenderSystem* _system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};

