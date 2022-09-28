#include "Efeect.h"

bool Efeect::Updata()
{
    m_fEffectTimer += I_Timer.m_fDeltaTime;
    if (m_fStep <= m_fEffectTimer)
    {
        m_fEffectTimer -= m_fStep;
        m_iIndex++;
    }
    if (m_iIndex >= m_iMaxIndex)
    {
        return false;
    }
    Rect rt = m_pSprite->m_uvArray[m_iIndex];
    m_tRect = rt;
    //ector2D vAdd = temp * 300.0f * I_Timer.m_fDeltaTime;
    //m_vPos = m_vPos + vAdd;
    m_rtCollision.x0 = m_vPos.x;
    m_rtCollision.y0 = m_vPos.y;
    return true;
}
