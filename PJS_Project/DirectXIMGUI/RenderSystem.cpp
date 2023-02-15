#include "RenderSystem.h"
#include <exception>
#include "imgui_impl_dx11.h"

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

	// 디바이스 컨텍스트
	ComPtr<ID3D11DeviceContext> _imm_Context;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		hr = D3D11CreateDevice(NULL, driver_type[driver_type_index], NULL, NULL, feature_levels, num_feature_level,
			D3D11_SDK_VERSION, _d3d_Device.GetAddressOf(), &_feature_level, _imm_Context.GetAddressOf());

		if (SUCCEEDED(hr))
			break;
		++driver_type_index;
	}
	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("RenderSystem not create successfully");
	}
	// 디바이스 컨텍스크 클래스 생성 디바이스 컨텍스트 전달
	_immContext = std::make_shared<DeviceContext>(_imm_Context.Get(), this);

	// dxgi 설정
	_d3d_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)_dxgi.GetAddressOf());
	_dxgi->GetParent(__uuidof(IDXGIAdapter), (void**)_dxgi_Adapter.GetAddressOf());
	_dxgi_Adapter->GetParent(__uuidof(IDXGIFactory), (void**)_dxgi_Factory.GetAddressOf());

	InitRasterizerState();
	InitDepthStencilState();
	// Init imgui d3d impl
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplDX11_Init(_d3d_Device.Get(), _imm_Context.Get());
}

RenderSystem::~RenderSystem()
{
	
}


SwapChainPtr RenderSystem::CreateSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;
	try
	{
		sc = std::make_shared<MSwapChain>(hwnd, width, height, this);
	}
	catch (...) {}
	return sc;
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return _immContext;
}



MVertexShaderPtr RenderSystem::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	MVertexShaderPtr _vs = std::make_shared<MVertexShader>(shader_byte_code, byte_code_size, this);
	return _vs;
}

PixelShaderPtr RenderSystem::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShaderPtr _ps = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
	return _ps;
}

bool RenderSystem::CompileVertexShader(const WCHAR* file_name, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size)
{
	HRESULT hr;
	ComPtr<ID3DBlob> errCode;
	hr = D3DCompileFromFile(file_name, nullptr, nullptr, point_name, "vs_5_0", NULL, NULL, _vsBlob.GetAddressOf(), errCode.GetAddressOf());
	if (FAILED(hr))
	{
		if (errCode != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
		assert(false);
		return false;
	}
	*shader_byte_code = _vsBlob->GetBufferPointer();
	*byte_code_size = _vsBlob->GetBufferSize();


	return true;
}

bool RenderSystem::CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size)
{
	HRESULT hr;
	ComPtr<ID3DBlob> errCode = nullptr;
	// 쉐이더 컴파일러

	hr = D3DCompileFromFile(filename, nullptr, nullptr, point_name, "ps_5_0", NULL, NULL, _psBlob.GetAddressOf(), errCode.GetAddressOf());
	if (FAILED(hr))
	{
		if (errCode.Get() != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
	}
	*shader_byte_code = _psBlob->GetBufferPointer();
	*byte_code_size = _psBlob->GetBufferSize();
	return true;
}

void RenderSystem::SetRaterizerState(bool cull_front, bool wire_frame)
{
	if (wire_frame)
	{
		if (cull_front)
			_immContext->GetDeviceContext()->RSSetState(fill_wireframe_front_.Get());
		else
			_immContext->GetDeviceContext()->RSSetState(fill_wireframe_back_.Get());
	}
	else
	{
		if (cull_front)
			_immContext->GetDeviceContext()->RSSetState(_cull_front_state.Get());
		else
			_immContext->GetDeviceContext()->RSSetState(_cull_back_state.Get());
	}

}

void RenderSystem::SetDepthStencilState()
{
	UINT ref = 0x01;
	// 깊이 활성화
	_immContext->GetDeviceContext()->OMSetDepthStencilState(dss_depth_enable_.Get(), ref);
	
}

void RenderSystem::InitRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	// 앞으로 렌더링 와이어 프레임
	_d3d_Device->CreateRasterizerState(&desc, fill_wireframe_front_.GetAddressOf());
	// 뒤로 렌더링 와이어 프레임
	desc.CullMode = D3D11_CULL_BACK;
	_d3d_Device->CreateRasterizerState(&desc, fill_wireframe_back_.GetAddressOf());
	// 뒤로 렌더링 솔리드
	desc.FillMode = D3D11_FILL_SOLID;
	_d3d_Device->CreateRasterizerState(&desc, _cull_back_state.GetAddressOf());
	desc.CullMode = D3D11_CULL_FRONT;
	_d3d_Device->CreateRasterizerState(&desc, _cull_front_state.GetAddressOf());
}

void RenderSystem::InitDepthStencilState()
{
	HRESULT hr;
	// 깊이 버퍼 상태값 세팅
	D3D11_DEPTH_STENCIL_DESC dsDescDepth;
	ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	dsDescDepth.StencilEnable = FALSE;
	dsDescDepth.StencilReadMask = 1;
	dsDescDepth.StencilWriteMask = 1;
	dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	// 디폴트 세팅
	// 깊이 버퍼 활성화
	dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	if (FAILED(hr = _d3d_Device->CreateDepthStencilState(&dsDescDepth, &dss_depth_enable_)))
	{
		assert(false);
	}
	// 깊이 버퍼 비교 비 활성화
	dsDescDepth.DepthEnable = FALSE;
	if (FAILED(hr = _d3d_Device->CreateDepthStencilState(&dsDescDepth, &dss_depth_disable_)))
	{
		assert(false);
	}
	// 깊이 버퍼 활성화, 마스크 쓰지 않기
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDescDepth.DepthEnable = TRUE;
	dsDescDepth.StencilEnable = FALSE;
	if (FAILED(hr = _d3d_Device->CreateDepthStencilState(&dsDescDepth, &dss_depth_enable_no_write_)))
	{
		assert(false);
	}
	// 깊이 버퍼 비 활성화, 마스크 쓰지 않기
	dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDescDepth.DepthEnable = FALSE;
	dsDescDepth.StencilEnable = FALSE;
	if (FAILED(hr = _d3d_Device->CreateDepthStencilState(&dsDescDepth, &dss_depth_disable_no_write)))
	{
		assert(false);
	}
}


MVertexBufferPtr RenderSystem::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	return std::make_shared<MVertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
}

IndexBufferPtr RenderSystem::CreateIndexBuffer(void* list_indices, UINT size_list)
{
	return std::make_shared<IndexBuffer>(list_indices, size_list, this);
}

ConstantBufferPtr RenderSystem::CreateConstantBuffer(void* buffer, UINT size_buffer)
{
	return std::make_shared<ConstantBuffer>(buffer, size_buffer,this);
}
