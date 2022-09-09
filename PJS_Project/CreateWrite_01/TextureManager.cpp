#include "TextureManager.h"

void TextureManager::SetDvice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
	m_p3dDevice = _p3dDevice;
	m_pImmediateContext = _pImmediateContext;
}

Texture* TextureManager::LoadTexture(std::wstring _fileName)
{
	HRESULT hr;
	// 중복제거
	// 쉐이더를 생성 할 때 중복되는것이 있으면 그 쉐이더를 반환한다.
	auto data = FindTexture(_fileName);
	if (data != nullptr)
		return data;

	Texture* newTexture = new Texture;
	if (newTexture)
	{
		hr = newTexture->Load(m_p3dDevice, m_pImmediateContext, _fileName);
		if (SUCCEEDED(hr))
		{
			m_TextureList.insert(std::make_pair(_fileName, newTexture));
		}
	}
	return newTexture;
}

Texture* TextureManager::FindTexture(std::wstring _fileName)
{
	auto iter = m_TextureList.find(_fileName);
	if (iter != m_TextureList.end())
	{
		return iter->second;
	}
	return nullptr;
}

bool TextureManager::Release()
{
	for (auto data: m_TextureList)
	{
		Texture* pdata = data.second;
		if (pdata)
			pdata->Release();
		delete pdata;
	}
	return false;
}
