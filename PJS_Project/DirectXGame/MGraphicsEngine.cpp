#include "MGraphicsEngine.h"
#include "MVertexBuffer.h"

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

std::unique_ptr<MSwapChain> MGraphicsEngine::CreateSwapChain()
{
	return std::make_unique<MSwapChain>();
}

DeviceContext* MGraphicsEngine::getImmediateDeviceContext()
{
	return this->_immContext.get();
}

bool MGraphicsEngine::CreateShader()
{
	HRESULT hr;
	// 쉐이더 생성
	ComPtr<ID3DBlob> errCode = nullptr;
	// 쉐이더 컴파일러
	hr = D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "mainvs", "vs_5_0", NULL, NULL, _vsBlob.GetAddressOf(), errCode.GetAddressOf());
	if (FAILED(hr))
	{
		if (errCode != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
	}
	hr = D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "mainps", "ps_5_0", NULL, NULL, _psBlob.GetAddressOf(), errCode.GetAddressOf());
	if (FAILED(hr))
	{
		if (errCode != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
	}
	hr = _d3d_Device->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vsShader.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
		return false;
	}
	hr = _d3d_Device->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _psShader.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
		return false;
	}
	return true;
}

bool MGraphicsEngine::SetShader()
{
	_immContext->GetDeviceContext()->VSSetShader(_vsShader.Get(), nullptr, 0);
	_immContext->GetDeviceContext()->PSSetShader(_psShader.Get(), nullptr, 0);
	return true;
}

bool MGraphicsEngine::GetShaderBufferSize(void** bytecode, UINT* size)
{
	*bytecode = this->_vsBlob->GetBufferPointer();
	*size = (UINT)this->_vsBlob->GetBufferSize();
	return true;
}

MGraphicsEngine* MGraphicsEngine::get()
{
	static MGraphicsEngine engine;
	return &engine;
}

std::shared_ptr<MVertexBuffer> MGraphicsEngine::CreateVertexBuffer()
{
	return std::make_shared<MVertexBuffer>();
}
