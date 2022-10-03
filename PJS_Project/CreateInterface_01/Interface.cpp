#include "Interface.h"

bool Interface::Frame()
{
    return false;
}

void Interface::SetPosition(Vector2D _pos)
{
    m_vPosition = _pos;
    ScreenToNDC();
    Object2D::UpdateVertexBuffer();
}

void Interface::ScreenToNDC()
{
    /*Vector2D vDrawSize;
    vDrawSize.x = m_rtInit.xSize / 2.0f;
    vDrawSize.y = m_rtInit.ySize / 2.0f;*/
    //m_rtCollision = { m_vPosition.x - vDrawSize.x, m_vPosition.y - vDrawSize.y, m_rtInit.xSize, m_rtInit.ySize };
    m_vDrawPos.x = (m_vPosition.x / g_rtClient.right) * 2.0f - 1.0f;
    m_vDrawPos.y = -((m_vPosition.y / g_rtClient.bottom) * 2.0f - 1.0f);
    m_vDrawSize.x = (m_rtInit.xSize / g_rtClient.right) * 2;
    m_vDrawSize.y = (m_rtInit.ySize / g_rtClient.bottom) * 2;
}


