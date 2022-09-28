#include "Object2D.h"

bool Object2D::Frame()
{
    return true;
}

void Object2D::SetDirection(Vector2D _dir)
{
    return;
}

void Object2D::SetRect(Rect _Pos)
{
    m_rtInit = _Pos;
    
    m_ptImageSize.x = m_Desc.Width;
    m_ptImageSize.y = m_Desc.Height;

    m_rtUV.x0 = _Pos.x0 / m_ptImageSize.x;
    m_rtUV.y0 = _Pos.y0 / m_ptImageSize.y;
    m_rtUV.xSize = _Pos.xSize / m_ptImageSize.x;
    m_rtUV.ySize = _Pos.ySize / m_ptImageSize.y;
}

void Object2D::SetPosition(Vector2D _pos)
{
    m_vPosition = _pos;
    Vector2D vDrawSize;
    vDrawSize.x = m_rtInit.xSize / 2.0f;
    vDrawSize.y = m_rtInit.ySize / 2.0f;
    m_rtCollision = { _pos.x - vDrawSize.x, _pos.y - vDrawSize.y, m_rtInit.xSize, m_rtInit.ySize };
    m_vDrawPos.x = (m_rtCollision.x0 / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((m_rtCollision.y0 / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.xSize / g_rtClient.right) * 2;
    m_vDrawSize.y = (m_rtInit.ySize / g_rtClient.bottom) * 2;
    //UpdateVertexBuffer();

    m_vCenterPoint.x = (m_vPosition.x + m_vPosition.x + m_rtInit.xSize) / 2;
    m_vCenterPoint.y = (m_vPosition.y + m_vPosition.y + m_rtInit.ySize) / 2;
    UpdateVertexBuffer();
}



void Object2D::UpdateVertexBuffer()
{
    m_pVertexList[0].position = { m_vDrawPos.x, m_vDrawPos.y, 0.0f };
    m_pVertexList[1].position = { m_vDrawPos.x + m_vDrawSize.x,m_vDrawPos.y , 0.0f };
    m_pVertexList[2].position = { m_vDrawPos.x, m_vDrawPos.y - m_vDrawSize.y, 0.0f };
    m_pVertexList[3].position = { m_vDrawPos.x + m_vDrawSize.x,m_vDrawPos.y - m_vDrawSize.y, 0.0f };

    m_pVertexList[0].texture = { m_rtUV.x0, m_rtUV.y0 };
    m_pVertexList[1].texture = { m_rtUV.x0 + m_rtUV.xSize, m_rtUV.y0 };
    m_pVertexList[2].texture = { m_rtUV.x0, m_rtUV.y0 + m_rtUV.ySize };
    m_pVertexList[3].texture = { m_rtUV.x0 + m_rtUV.xSize, m_rtUV.y0 + m_rtUV.ySize };

    m_pImmediateContext->UpdateSubresource(m_pVertexBuffer, NULL, NULL, &m_pVertexList.at(0), 0, 0);
}
