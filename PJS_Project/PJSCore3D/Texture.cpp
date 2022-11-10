#include "Texture.h"

bool Texture::Init()
{
	return true;
}

bool Texture::Frame()
{
	return true;
}

bool Texture::Render()
{
	return true;
}

bool Texture::Release()
{
	if (m_pTexture)
		m_pTexture->Release();
	if (m_pSrvTexture)
		m_pSrvTexture->Release();
	m_pTexture = nullptr;
	m_pSrvTexture = nullptr;
	return true;
}

HRESULT Texture::Load(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _fileName)
{
	HRESULT hr;
	DirectX::DDS_ALPHA_MODE alphaMode;
	hr = DirectX::CreateWICTextureFromFile(_p3dDevice, _pImmediateContext, _fileName.c_str(), &m_pTexture, &m_pSrvTexture);
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(_p3dDevice, _pImmediateContext, _fileName.c_str(), &m_pTexture, &m_pSrvTexture, 0, &alphaMode);
	}
	if (FAILED(hr))
	{
		//assert(false);
		return hr;
	}
}
