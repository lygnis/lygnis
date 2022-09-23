#include "Bullet.h"

bool Bullet::Frame()
{
    Vector2D _vPos = m_vPosition;
    m_fSpeed = 50.0f;
    m_fMass = 10.0f;
    m_vForce.y += GRVITY_AMOUNT * I_Timer.m_fDeltaTime / m_fPower;
    _vPos.x += m_fMass * m_vForce.x * m_fSpeed *I_Timer.m_fDeltaTime;
    _vPos.y += m_fMass * m_vForce.y * m_fSpeed * I_Timer.m_fDeltaTime;
    m_vFirePoint = { m_rtCollision.x0, m_rtCollision.y0 };
    SetPosition(_vPos);
    if (m_vDrawPos.y < -1.0f || m_vDrawPos.y > 1.0f)
    {
        return false;
    }
    if (m_vDrawPos.x < -1.0f|| m_vDrawPos.x > 1.0f)
    {
        return false;
    }
    return true;
}

void Bullet::GetMousePosition(POINT _vec, Vector2D _center)
{
    m_vDir.x = _vec.x - _center.x;
    m_vDir.y = _vec.y - _center.y;
    m_vDir = m_vDir.Normalized();
    m_vForce = m_vDir;
}

Bullet::Bullet()
    /*: m_vForce(m_vDir)*/
{
}
