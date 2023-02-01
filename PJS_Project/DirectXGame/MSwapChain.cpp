#include "MSwapChain.h"
#include "RenderSystem.h"
#include <exception>

MSwapChain::MSwapChain(HWND hwnd, UINT width, UINT height ,RenderSystem* system) : _system(system)
{
	// ����̽� �ޱ�
	ID3D11Device* device = _system->_d3d_Device.Get();
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
	HRESULT hr = _system->_dxgi_Factory->CreateSwapChain(device, &desc, _gi_swapChain.GetAddressOf());
	
	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("SwapChain not create successfully");
	}
	ReloadBuffers(width, height);
}

void MSwapChain::Resize(UINT width, UINT height)
{
	HRESULT hr;
	_Rtv.ReleaseAndGetAddressOf();
	_Dsv.ReleaseAndGetAddressOf();

	hr = _gi_swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	ReloadBuffers(width, height);
}

bool MSwapChain::Present(bool vsync)
{
	// ����ۿ� �ٲ۴�.
	_gi_swapChain->Present(0, 0);
	return true;
}

void MSwapChain::ReloadBuffers(UINT width, UINT height)
{
	HRESULT hr;
	ID3D11Device* device = _system->_d3d_Device.Get();
	// �� ���� ��, ����Ÿ�ٺ並 �����´�
	ID3D11Texture2D* buffer = NULL;
	hr = _gi_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("SwapBuffer not create successfully");
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &_Rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("RenderTarget not create successfully");
	}
	// ���̹��� ����
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;

	hr = device->CreateTexture2D(&tex_desc, nullptr, &buffer);

	if (FAILED(hr))
	{
		throw std::exception("");
	}
	hr = device->CreateDepthStencilView(buffer, NULL, &_Dsv);
	buffer->Release();

	if (FAILED(hr))
	{
		assert(false);
		throw std::exception("RenderTarget not create successfully");
	}
}
