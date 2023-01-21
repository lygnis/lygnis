#pragma once
#include <d3d11.h>
#include "MSwapChain.h"
#include "MStd.h"
#include "DeviceContext.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
class MVertexBuffer;
//class MVertexShader;

class MGraphicsEngine
{
public:
	bool Init();
	bool Release();
public:
	MGraphicsEngine();
	~MGraphicsEngine();
public:
	// 스왑체인 클래스 생성
	std::shared_ptr<MSwapChain> CreateSwapChain();
	// 버텍스 버퍼 클래스 생성
	std::unique_ptr<MVertexBuffer> CreateVertexBuffer();
	std::unique_ptr<ConstantBuffer>CreateConstantBuffer();
	DeviceContext* getImmediateDeviceContext();
public:
	std::unique_ptr<MVertexShader> CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	std::unique_ptr<PixelShader> CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool CompileVertexShader(const WCHAR* filename, const CHAR* point_name,  void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
public:
	// 싱글톤
	static MGraphicsEngine* get();
private:
	ComPtr<ID3D11Device> _d3d_Device;
	//ComPtr<ID3D11DeviceContext> _imm_Context;
	ComPtr<IDXGIDevice>			_dxgi;
	ComPtr<IDXGIAdapter>		_dxgi_Adapter;
	ComPtr<IDXGIFactory>		_dxgi_Factory;
	ComPtr<ID3DBlob>			_vsBlob;
	ComPtr<ID3DBlob>			_psBlob;
	//ComPtr<ID3D11VertexShader>		_vsShader;
	//ComPtr<ID3D11PixelShader>		_psShader;
private:
	friend class MSwapChain;
	friend class MVertexBuffer;
	friend class MVertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
private:
	D3D_FEATURE_LEVEL _feature_level;
	std::unique_ptr<DeviceContext> _immContext;
};

