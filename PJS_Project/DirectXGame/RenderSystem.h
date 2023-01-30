#pragma once
#include <d3d11.h>
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

private:
	ComPtr<ID3D11Device> _d3d_Device;
	ComPtr<IDXGIDevice>			_dxgi;
	ComPtr<IDXGIAdapter>		_dxgi_Adapter;
	ComPtr<IDXGIFactory>		_dxgi_Factory;
	ComPtr<ID3DBlob>			_vsBlob;
	ComPtr<ID3DBlob>			_psBlob;
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

