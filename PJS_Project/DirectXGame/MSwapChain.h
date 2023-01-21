#pragma once
#include "MStd.h"

using namespace Microsoft::WRL;

class DeviceContext;

class MSwapChain
{
public:
	MSwapChain() {}
	~MSwapChain() {}
public:
	bool Init(HWND hwnd, UINT width, UINT height);
	bool Present(bool vsync);
	bool Release();
private:
	ComPtr<IDXGISwapChain> _gi_swapChain;
	ComPtr<ID3D11RenderTargetView> _Rtv;
private:
	friend class DeviceContext;
};

