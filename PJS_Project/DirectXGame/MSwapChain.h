#pragma once
#include "MStd.h"

using namespace Microsoft::WRL;


class MSwapChain
{
public:
	// 스왑체인 생성
	MSwapChain(HWND hwnd, UINT width, UINT height ,RenderSystem* system);
	~MSwapChain() {}
public:
	bool Present(bool vsync);
private:
	ComPtr<IDXGISwapChain> _gi_swapChain;
	ComPtr<ID3D11RenderTargetView> _Rtv;
	ComPtr<ID3D11DepthStencilView> _Dsv;
	RenderSystem* _system = nullptr;
private:
	friend class DeviceContext;
};

