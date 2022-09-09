#include "DynamicObj.h"

bool DynamicObj::Frame()
{
	SetPosition(m_vPos);
	return true;
}

void DynamicObj::SetRect(Rect _rt)
{
	m_rtInit = _rt;
	m_ptImageSize.x = m_pTexture->m_Desc.Width;
	m_ptImageSize.y = m_pTexture->m_Desc.Height;
	m_rtUV.x0 = _rt.x0 / m_ptImageSize.x;
	m_rtUV.y0 = _rt.y0 / m_ptImageSize.y;
	m_rtUV.xSize = _rt.xSize / m_ptImageSize.x;
	m_rtUV.ySize = _rt.ySize / m_ptImageSize.y;
}

void DynamicObj::SetDirection()
{
}

void DynamicObj::SetPosition(Vector2D _vec)
{
	m_vPos = _vec;
	m_vDrawPos.x = ((m_vPos.x / g_rtClient.right) * 2.0f) - 1.0f;
	m_vDrawPos.y = ((m_vPos.y / g_rtClient.bottom) * 2.0f) - 1.0f;
	m_vDrawSize.x = (m_rtInit.xSize / g_rtClient.right) * 2;
	m_vDrawSize.y = (m_rtInit.ySize / g_rtClient.bottom) * 2;

	UpdateVertexBuffer();
}

void DynamicObj::UpdateVertexBuffer()
{
	m_pVertexList[0].p = { m_vDrawPos.x, m_vDrawPos.y, 0.0f };
	m_pVertexList[1].p = { m_vDrawPos.x + m_vDrawSize.x,m_vDrawPos.y , 0.0f };
	m_pVertexList[2].p = { m_vDrawPos.x, m_vDrawPos.y- m_vDrawSize.y, 0.0f };
	m_pVertexList[3].p = m_pVertexList[2].p;
	m_pVertexList[4].p = m_pVertexList[1].p;
	m_pVertexList[5].p = { m_vDrawPos.x + m_vDrawSize.x,m_vDrawPos.y - m_vDrawSize.y, 0.0f };

	m_pVertexList[0].t = { m_rtUV.x0, m_rtUV.y0 };
	m_pVertexList[1].t = { m_rtUV.x0 +m_rtUV.xSize, m_rtUV.y0 };
	m_pVertexList[2].t = { m_rtUV.x0, m_rtUV.y0+m_rtUV.ySize };
	m_pVertexList[3].t = m_pVertexList[2].t;
	m_pVertexList[4].t = m_pVertexList[1].t;
	m_pVertexList[5].t = { m_rtUV.x0+ m_rtUV.xSize, m_rtUV.y0 + m_rtUV.ySize };

	m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_pVertexList.at(0), 0, 0);
}
