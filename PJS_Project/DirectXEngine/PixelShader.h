#pragma once
#include "MStd.h"

class PixelShader
{
public:
	PixelShader(const wchar_t* full_path, const char* entry_point ,RenderSystem* system);
	~PixelShader() {};
private:
	ComPtr<ID3D11PixelShader> _psShader;
	RenderSystem* _system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};

