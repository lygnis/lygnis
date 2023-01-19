#include "MSwapChain.h"
#include "MGraphicsEngine.h"
bool MSwapChain::Init(HWND hwnd, UINT width, UINT height)
{
	// ����̽� �ޱ�
	ID3D11Device* device = MGraphicsEngine::get()->_d3d_Device.Get();
	// ����ü�� ����ũ ����
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// ������ �ڵ�� ���� swapchain ����
	HRESULT hr = MGraphicsEngine::get()->_dxgi_Factory->CreateSwapChain(device, &desc, _swapChain.GetAddressOf());
	
	if (FAILED(hr))
	{
		assert(false);
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		assert(false);
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &_Rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		assert(false);
		return false;
	}

	return true;
}

bool MSwapChain::Present(bool vsync)
{
	// ����ۿ� �ٲ۴�.
	_swapChain->Present(0, 0);
	return true;
}

bool MSwapChain::Release()
{
	return false;
}
