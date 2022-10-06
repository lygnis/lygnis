#include "Bullet.h"
#include "Timer.h"
bool Bullet::Frame()
{
    Vector2D _vPos = m_vPosition;
    m_fSpeed = 50.0f;
    m_fMass = 10.0f;
    m_vForce.y += GRVITY_AMOUNT * I_Timer.m_fDeltaTime / m_fPower;
    float m_temp = I_Timer.m_fDeltaTime;
    _vPos.x += m_fMass * m_vForce.x * m_fSpeed *I_Timer.m_fDeltaTime;
    _vPos.y += m_fMass * m_vForce.y * m_fSpeed * I_Timer.m_fDeltaTime;
    m_vFirePoint = { m_rtCollision.x0, m_rtCollision.y0 };
    SetPosition(_vPos, m_vCameraPos);
    return true;
}

void Bullet::GetMousePosition(POINT _vec, Vector2D _center, Vector2D _vCameraPos)
{
    if (_vec.x >= 400)
        _vec.x = 400;
    m_vDir.x = _vec.x - _center.x + _vCameraPos.x -400;
    m_vDir.y = _vec.y - _center.y + _vCameraPos.y -300;
    m_vDir = m_vDir.Normalized();
    m_vForce = m_vDir;
}

Bullet::Bullet()
    /*: m_vForce(m_vDir)*/
{
}
