#include "MGraphicsEngine.h"
#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "ConstantBuffer.h"

bool MGraphicsEngine::Init()
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
		return false;
	}
	// 디바이스 컨텍스크 클래스 생성 디바이스 컨텍스트 전달
	_immContext = std::make_unique<DeviceContext>(_imm_Context.Get());

	// dxgi 설정
	_d3d_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)_dxgi.GetAddressOf());
	_dxgi->GetParent(__uuidof(IDXGIAdapter), (void**)_dxgi_Adapter.GetAddressOf());
	_dxgi_Adapter->GetParent(__uuidof(IDXGIFactory), (void**)_dxgi_Factory.GetAddressOf());


	return true;
}

bool MGraphicsEngine::Release()
{

	return true;
}

MGraphicsEngine::MGraphicsEngine()
{
}

MGraphicsEngine::~MGraphicsEngine()
{
}

std::shared_ptr<MSwapChain> MGraphicsEngine::CreateSwapChain()
{
	return std::make_unique<MSwapChain>();
}

DeviceContext* MGraphicsEngine::getImmediateDeviceContext()
{
	return _immContext.get();
}



std::unique_ptr<MVertexShader> MGraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	std::unique_ptr<MVertexShader> _vs{ new MVertexShader() };
	if (!_vs->Init(shader_byte_code, byte_code_size))
	{
		assert(false);
		return nullptr;
	}
	return _vs;
}

std::unique_ptr<PixelShader> MGraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	std::unique_ptr<PixelShader> _ps { new PixelShader() };
	if (!_ps->Init(shader_byte_code, byte_code_size))
	{
		assert(false);
		return nullptr;
	}
	return _ps;
}

bool MGraphicsEngine::CompileVertexShader(const WCHAR* file_name, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size )
{
	HRESULT hr;
	ComPtr<ID3DBlob> errCode;
	hr = D3DCompileFromFile(file_name, nullptr, nullptr, point_name , "vs_5_0", NULL, NULL, _vsBlob.GetAddressOf(), errCode.GetAddressOf());
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

bool MGraphicsEngine::CompilePixelShader(const WCHAR* filename, const CHAR* point_name, void** shader_byte_code, size_t* byte_code_size)
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

MGraphicsEngine* MGraphicsEngine::get()
{
	static MGraphicsEngine engine;
	return &engine;
}

std::unique_ptr<MVertexBuffer> MGraphicsEngine::CreateVertexBuffer()
{
	return std::make_unique<MVertexBuffer>();
}

std::unique_ptr<ConstantBuffer> MGraphicsEngine::CreateConstantBuffer()
{
	return std::make_unique<ConstantBuffer>();
}
