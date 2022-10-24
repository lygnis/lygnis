#include "DxState.h"
#include <cassert>
ID3D11SamplerState* DxState::g_pDefaultSSWrap = nullptr;
ID3D11SamplerState* DxState::g_pDefaultSSMirror = nullptr;
ID3D11BlendState* DxState::g_pAlphaBlend = nullptr;

ID3D11RasterizerState* DxState::g_pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DxState::g_pDefaultRSSolid = nullptr;
ID3D11DepthStencilState* DxState::g_pDefaultDepthStencil = nullptr;
ID3D11DepthStencilState* DxState::g_pGreaterDepthStencil = nullptr;
bool DxState::SetState(ID3D11Device* _pd3dDevice)
{
	HRESULT hr;
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;     // �ֱ��� ���͸�, �̹����� ��Ʈ �������� ��µȴ�.
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV= D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    /*sd.MipLODBias;            2D������ ������� �ʴ´�.
    sd.MaxAnisotropy;
    sd.ComparisonFunc;
    sd.BorderColor[4];
    sd.MinLOD;
    sd.MaxLOD;*/
    // Wrap Ÿ�� ���
    hr = _pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSWrap);
    assert(SUCCEEDED(hr));

    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;// �ֱ��� ���͸�
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    // MIRROR ���
    hr = _pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSMirror);
    assert(SUCCEEDED(hr));

    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.DepthClipEnable = TRUE;
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    // ���̾� ������ ����
    hr= _pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);
    assert(SUCCEEDED(hr));

    rd.FillMode = D3D11_FILL_SOLID;
    hr = _pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);
    assert(SUCCEEDED(hr));

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    //bd.IndependentBlendEnable = TRUE;
    // ȥ�� : ���´�. 
    // ���(������) d-RGBA : ����ۿ� �̹� ������ �Ǿ� �ִ� ���,
    // ���� �ҽ� :  s-RGBA : ���� ������ �Ϸ��� ��ü, �ȼ����̴�
    //  RGB ������ ȥ���ϴ� ���
    // ���ĺ��� ����
    // finalColor = SrcColor*SrcAlpha+DestColor*(1.0f-SrcApha);
    // apha= 1.0f (������), alpha=0.0f (����), alpha 0~1 (������)
    // finalColor = SrcColor*1.0f+DestColor*(1.0f-1.0f);
    // finalColor = SrcColor*0.0f+DestColor*(1.0f-0.0f);
    // finalColor = SrcColor*0.5f+DestColor*(1.0f-0.5f);
    bd.RenderTarget[0].BlendEnable = TRUE;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    //  A ������ ȥ���ϴ� ���
    // finalAlpha = SrcAlpha*1.0f+DestAlpha*0.0f;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    // ���� ����
    _pd3dDevice->CreateBlendState(&bd, &g_pAlphaBlend);

    // ���� ���� ���� ����
    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.DepthEnable = TRUE;
    // 0.5f * mask(1) --> output(0.5)
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    dsd.StencilEnable =FALSE; 
    dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
   /* D3D11_DEPTH_STENCILOP_DESC FrontFace;
    D3D11_DEPTH_STENCILOP_DESC BackFace;*/
    hr = _pd3dDevice->CreateDepthStencilState(&dsd, &g_pDefaultDepthStencil);
    dsd.DepthFunc = D3D11_COMPARISON_GREATER;
    hr = _pd3dDevice->CreateDepthStencilState(&dsd, &g_pGreaterDepthStencil);
	return true;
}

bool DxState::Release()
{
    if (g_pAlphaBlend) g_pAlphaBlend->Release();
    if (g_pDefaultSSWrap) g_pDefaultSSWrap->Release();
    if (g_pDefaultSSMirror) g_pDefaultSSMirror->Release();
    if (g_pDefaultRSSolid)g_pDefaultRSSolid->Release();
    if (g_pDefaultRSWireFrame)g_pDefaultRSWireFrame->Release();
    if (g_pDefaultDepthStencil)g_pDefaultDepthStencil->Release();
    if (g_pGreaterDepthStencil)g_pGreaterDepthStencil->Release();
	return true;
}
