#include "DxState.h"
#include <cassert>
ID3D11SamplerState* DxState::g_pDefaultSS = nullptr;
bool DxState::SetState(ID3D11Device* _pd3dDevice)
{
	HRESULT hr;
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;     // 최근점 필터링, 이미지가 도트 형식으로 출력된다.
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    /*sd.MipLODBias;            2D에서는 사용하지 않는다.
    sd.MaxAnisotropy;
    sd.ComparisonFunc;
    sd.BorderColor[4];
    sd.MinLOD;
    sd.MaxLOD;*/
    hr = _pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSS);
    assert(SUCCEEDED(hr));
	return true;
}

bool DxState::Release()
{
    if (g_pDefaultSS)g_pDefaultSS->Release();
	return true;
}
