#pragma once
#include "MStd.h"


class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
public:
	// ����ü�� Ŭ���� ����
	SwapChainPtr		CreateSwapChain(HWND hwnd, UINT width, UINT height);
	// ���� Ŭ���� ����
	MVertexBufferPtr	CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	IndexBufferPtr		CreateIndexBuffer(void* list_indices, UINT size_list);
	ConstantBufferPtr	CreateConstantBuffer(void* buffer, UINT size_buffer);
	// ���ؽ�Ʈ ��ȯ
	DeviceContextPtr	getImmediateDeviceContext();
public:
	// ���̴� ����
	MVertexShaderPtr	CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr		CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);
	// ���̴� ������
	bool				CompileVertexShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	bool				CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size);
	void SetRaterizerState(bool cull_front);
private:
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
private:
	friend class MSwapChain;
	friend class MVertexBuffer;
	friend class MVertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
	friend class Texture;
private:
	DeviceContextPtr	_immContext;
};

