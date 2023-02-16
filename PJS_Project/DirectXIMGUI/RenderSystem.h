#pragma once
#include "MSwapChain.h"
#include "MStd.h"
#include "DeviceContext.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
//#include "MGraphicsEngine.h"
#include "IndexBuffer.h"
#include "MVertexBuffer.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
public:
	// 스왑체인 클래스 생성
	SwapChainPtr		CreateSwapChain(HWND hwnd, UINT width, UINT height);
	// 버퍼 클래스 생성
	MVertexBufferPtr	CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	IndexBufferPtr		CreateIndexBuffer(void* list_indices, UINT size_list);
	ConstantBufferPtr	CreateConstantBuffer(void* buffer, UINT size_buffer);
	// 콘텍스트 반환
	DeviceContextPtr	getImmediateDeviceContext();
public:
	// 쉐이더 생성
	MVertexShaderPtr	CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr		CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);
	// 쉐이더 컴파일
	bool				CompileVertexShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	bool				CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	void SetRaterizerState(bool cull_front, bool wire_frame);
	void SetDepthStencilState(bool on_z_buffer, bool z_buffer_write);
private:
	void InitRasterizerState();
	void InitDepthStencilState();
	void InitAlphaBelnd();
private:
	ComPtr<ID3D11Device>		_d3d_Device;
	ComPtr<IDXGIDevice>			_dxgi;
	ComPtr<IDXGIAdapter>		_dxgi_Adapter;
	ComPtr<IDXGIFactory>		_dxgi_Factory;
	ComPtr<ID3DBlob>			_vsBlob;
	ComPtr<ID3DBlob>			_psBlob;
	ComPtr<ID3D11RasterizerState> _cull_front_state;
	ComPtr<ID3D11RasterizerState> _cull_back_state;
	ComPtr<ID3D11RasterizerState> fill_wireframe_front_;
	ComPtr<ID3D11RasterizerState> fill_wireframe_back_;
private:
	ComPtr<ID3D11DepthStencilState> dss_depth_enable_;
	ComPtr<ID3D11DepthStencilState> dss_depth_disable_;
	ComPtr<ID3D11DepthStencilState> dss_depth_enable_no_write_;
	ComPtr<ID3D11DepthStencilState> dss_depth_disable_no_write;
private:
	ComPtr<ID3D11BlendState> alpha_blend_;
	ComPtr<ID3D11BlendState> no_alpha_blend_;
private:
	friend class MSwapChain;
	friend class MVertexBuffer;
	friend class MVertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
	friend class Texture;
private:
	D3D_FEATURE_LEVEL	_feature_level;
	DeviceContextPtr	_immContext;
};

