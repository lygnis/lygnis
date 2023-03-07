#include "RenderSystem.h"
#include <exception>
#include "MSwapChain.h"
#include "DeviceContext.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "MVertexBuffer.h"

RenderSystem::RenderSystem()
{
D3D_DRIVER_TYPE driver_type[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_type);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_level = ARRAYSIZE(feature_levels);

	HRESULT hr;

	// ����̽� ���ؽ�Ʈ
	ComPtr<ID3D11DeviceContext> _imm_Context;
	D3D_FEATURE_LEVEL feature_level = {};

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		hr = D3D11CreateDevice(NULL, driver_type[driver_type_index], NULL, NULL, feature_levels, num_feature_level,
			D3D11_SDK_VERSION, _d3d_Device.GetAddressOf(), &feature_level, _imm_Context.GetAddressOf());

		if (SUCCEEDED(hr))
			break;
		++driver_type_index;
	}
	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("RenderSystem not create successfully");
	}
	// ����̽� ���ؽ�ũ Ŭ���� ���� ����̽� ���ؽ�Ʈ ����
	_immContext = std::make_shared<DeviceContext>(_imm_Context.Get(), this);

	// dxgi ����
	_d3d_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)_dxgi.GetAddressOf());
	_dxgi->GetParent(__uuidof(IDXGIAdapter), (void**)_dxgi_Adapter.GetAddressOf());
	_dxgi_Adapter->GetParent(__uuidof(IDXGIFactory), (void**)_dxgi_Factory.GetAddressOf());

	InitRasterizerState();
	CompilePrivateShaders();
}

RenderSystem::~RenderSystem()
{
}


SwapChainPtr RenderSystem::CreateSwapChain(HWND hwnd, UINT width, UINT height)
{
	return std::make_shared<MSwapChain>(hwnd, width, height, this);
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return _immContext;
}



MVertexShaderPtr RenderSystem::CreateVertexShader(const wchar_t* full_path, const char* entry_point)
{
	return std::make_shared<MVertexShader>(full_path, entry_point, this);
}

PixelShaderPtr RenderSystem::CreatePixelShader(const wchar_t* full_path, const char* entry_point)
{
	return std::make_shared<PixelShader>(full_path, entry_point, this);
}

//bool RenderSystem::CompileVertexShader(const WCHAR* file_name, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size)
//{
//	HRESULT hr;
//	ComPtr<ID3DBlob> errCode;
//	hr = D3DCompileFromFile(file_name, nullptr, nullptr, point_name, "vs_5_0", NULL, NULL, _vsBlob.GetAddressOf(), errCode.GetAddressOf());
//	if (FAILED(hr))
//	{
//		if (errCode != NULL)
//		{
//			OutputDebugStringA((char*)errCode->GetBufferPointer());
//		}
//		assert(false);
//		return false;
//	}
//	*shader_byte_code = _vsBlob->GetBufferPointer();
//	*byte_code_size = _vsBlob->GetBufferSize();
//
//
//	return true;
//}
//
//bool RenderSystem::CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size)
//{
//	HRESULT hr;
//	ComPtr<ID3DBlob> errCode = nullptr;
//	// ���̴� �����Ϸ�
//
//	hr = D3DCompileFromFile(filename, nullptr, nullptr, point_name, "ps_5_0", NULL, NULL, _psBlob.GetAddressOf(), errCode.GetAddressOf());
//	if (FAILED(hr))
//	{
//		if (errCode.Get() != NULL)
//		{
//			OutputDebugStringA((char*)errCode->GetBufferPointer());
//		}
//	}
//	*shader_byte_code = _psBlob->GetBufferPointer();
//	*byte_code_size = _psBlob->GetBufferSize();
//	return true;
//}

void RenderSystem::SetRaterizerState(bool cull_front)
{
	if (cull_front)
		_immContext->GetDeviceContext()->RSSetState(_cull_front_state.Get());
	else
		_immContext->GetDeviceContext()->RSSetState(_cull_back_state.Get());
}

Texture2DPtr RenderSystem::CreateTexture(const wchar_t* full_path)
{
	return std::make_shared<Texture2D>(full_path, this);
}

Texture2DPtr RenderSystem::CreateTexture(const TMath::Rect& size, Texture2D::Type type)
{
	return std::make_shared<Texture2D>(size, type, this);
}

void RenderSystem::CompilePrivateShaders()
{
	HRESULT hr;
	ComPtr<ID3DBlob> blob;
	ComPtr<ID3DBlob> errCode;

	auto mesh_layout_code = R"(
struct VS_INPUT
{
	float4 position: POSITION;
	float2 texcoord: TEXCOORD;
	float3 normal: NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

VS_OUTPUT mainvs(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	return output;
}

	)";
	auto code_size = strlen(mesh_layout_code);

	hr = D3DCompile(mesh_layout_code, code_size, "VertexMeshLayoutShader",nullptr, nullptr,
		"mainvs", "vs_5_0",0,0,&blob, &errCode);
	if (FAILED(hr))
	{
		if (errCode != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
		assert(false);
		return;
	}
	memcpy(mesh_layout_byte_code_, blob->GetBufferPointer(), blob->GetBufferSize());
	mesh_layout_size_ = blob->GetBufferSize();
}

void RenderSystem::InitRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;

	_d3d_Device->CreateRasterizerState(&desc, _cull_front_state.GetAddressOf());

	desc.CullMode = D3D11_CULL_BACK;
	_d3d_Device->CreateRasterizerState(&desc, _cull_back_state.GetAddressOf());
}


MVertexBufferPtr RenderSystem::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list)
{
	return std::make_shared<MVertexBuffer>(list_vertices, size_vertex, size_list, this);
}

IndexBufferPtr RenderSystem::CreateIndexBuffer(void* list_indices, UINT size_list)
{
	return std::make_shared<IndexBuffer>(list_indices, size_list, this);
}

ConstantBufferPtr RenderSystem::CreateConstantBuffer(void* buffer, UINT size_buffer)
{
	return std::make_shared<ConstantBuffer>(buffer, size_buffer,this);
}
