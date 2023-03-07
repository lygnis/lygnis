#pragma once
#include "MStd.h"
#include "Texture2D.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
public:
	// 스왑체인 클래스 생성
	SwapChainPtr		CreateSwapChain(HWND hwnd, UINT width, UINT height);
	// 버퍼 클래스 생성
	MVertexBufferPtr	CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list);
	IndexBufferPtr		CreateIndexBuffer(void* list_indices, UINT size_list);
	ConstantBufferPtr	CreateConstantBuffer(void* buffer, UINT size_buffer);
	// 콘텍스트 반환
	DeviceContextPtr	getImmediateDeviceContext();
public:
	// 쉐이더 생성
	MVertexShaderPtr	CreateVertexShader(const wchar_t* full_path, const char* entry_point);
	PixelShaderPtr		CreatePixelShader(const wchar_t* full_path, const char* entry_point);
	// 쉐이더 컴파일
	//bool				CompileVertexShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	//bool				CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	void SetRaterizerState(bool cull_front);
	Texture2DPtr CreateTexture(const wchar_t* full_path);
	Texture2DPtr CreateTexture(const TMath::Rect&size, Texture2D::Type type);
private:
	void CompilePrivateShaders();
	void InitRasterizerState();
private:
	ComPtr<ID3D11Device>		_d3d_Device;
	ComPtr<IDXGIDevice>			_dxgi;
	ComPtr<IDXGIAdapter>		_dxgi_Adapter;
	ComPtr<IDXGIFactory>		_dxgi_Factory;
	ComPtr<ID3DBlob>			_vsBlob;
	ComPtr<ID3DBlob>			_psBlob;
	ComPtr<ID3D11RasterizerState> _cull_front_state;
	ComPtr<ID3D11RasterizerState> _cull_back_state;

	unsigned char mesh_layout_byte_code_[1024];
	size_t mesh_layout_size_ = 0;
private:
	friend class MSwapChain;
	friend class MVertexBuffer;
	friend class MVertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
	friend class Texture2D;
private:
	DeviceContextPtr	_immContext;
};

