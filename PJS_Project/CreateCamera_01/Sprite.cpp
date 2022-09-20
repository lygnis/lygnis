#include "Sprite.h"

void Sprite::SetPosition(Vector2D _pos)
{
	m_vPosition = _pos;
	Vector2D vDrawSize;
	vDrawSize.x = m_rtInit.xSize / 2.0f;
	vDrawSize.y = m_rtInit.ySize / 2.0f;
	m_rtCollision = { _pos.x - vDrawSize.x, _pos.y - vDrawSize.y, m_rtInit.xSize, m_rtInit.ySize };
	m_vDrawPos.x = (m_rtCollision.x0 / g_rtClient.right) * 2.0f -1.0f;
	m_vDrawPos.y = -(m_rtCollision.y0 / g_rtClient.bottom) * 2.0f - 1.0f;
	m_vDrawSize.x = (m_rtInit.xSize / g_rtClient.right)*2;
	m_vDrawSize.y = (m_rtInit.ySize / g_rtClient.bottom)*2;
	UpdateVertexBuffer();
}

HRESULT Sprite::Load(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _name)
{
	HRESULT hr;
	hr = SetDevice(_p3dDevice, _pImmediateContext);
	hr = Create(L"D:/Git_PJS_C/shader/DefaultShader.txt", L"D:/Git_PJS_C/data/bitmap1.bmp");
	if (FAILED(hr))
		return hr;
	return hr;
}
