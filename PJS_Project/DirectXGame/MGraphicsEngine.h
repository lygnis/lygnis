#pragma once
#include <d3d11.h>
#include "MSwapChain.h"
#include "MStd.h"
#include "DeviceContext.h"
//#include "MVertexBuffer.h"
class MVertexBuffer;
class MVertexShader;

class MGraphicsEngine
{
public:
	bool Init();
	bool Release();
public:
	MGraphicsEngine() {}
	~MGraphicsEngine() {}
public:
	std::unique_ptr<MSwapChain> CreateSwapChain();
	std::shared_ptr<MVertexBuffer> CreateVertexBuffer();
	DeviceContext* getImmediateDeviceContext();
public:
	bool CreateShader();
	bool SetShader();
	bool GetShaderBufferSize(void** bytecode, UINT* size);
	std::shared_ptr<MVertexShader> CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
public:
	// ΩÃ±€≈Ê
	static MGraphicsEngine* get();
private:
	ComPtr<ID3D11Device> _d3d_Device;
	//ComPtr<ID3D11DeviceContext> _imm_Context;
	ComPtr<IDXGIDevice>			_dxgi;
	ComPtr<IDXGIAdapter>		_dxgi_Adapter;
	ComPtr<IDXGIFactory>		_dxgi_Factory;
	ComPtr<ID3DBlob>			_vsBlob;
	ComPtr<ID3DBlob>			_psBlob;
	ComPtr<ID3D11VertexShader>		_vsShader;
	ComPtr<ID3D11PixelShader>		_psShader;
private:
	friend class MSwapChain;
	friend class MVertexBuffer;
	friend class MVertexShader;
private:
	D3D_FEATURE_LEVEL _feature_level;
	std::unique_ptr<DeviceContext> _immContext;
};

