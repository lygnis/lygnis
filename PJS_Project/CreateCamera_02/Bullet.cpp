#include "Bullet.h"
#include "Timer.h"
bool Bullet::Frame()
{
    Vector2D _vPos = m_vPosition;
    m_fSpeed = 50.0f;
    m_fMass = 10.0f;
    m_vForce.y += GRVITY_AMOUNT * I_Timer.m_fDeltaTime / m_fPower;
    float m_temp = I_Timer.m_fDeltaTime;
    Timer t = I_Timer;
    _vPos.x += m_fMass * m_vForce.x * m_fSpeed *I_Timer.m_fDeltaTime;
    _vPos.y += m_fMass * m_vForce.y * m_fSpeed * I_Timer.m_fDeltaTime;
    m_vFirePoint = { m_rtCollision.x0, m_rtCollision.y0 };
    SetPosition(_vPos, m_vCameraPos);
    if (_vPos.x < 500 || _vPos.y > 800.0f)
    {
        return false;
    }
    if (_vPos.x > 1700.0f|| _vPos.y <0)
    {
        return false;
    }
    return true;
}

void Bullet::GetMousePosition(POINT _vec, Vector2D _center, Vector2D _vCameraPos)
{
    m_vDir.x = _vec.x - _center.x + _vCameraPos.x -400;
    m_vDir.y = _vec.y - _center.y + _vCameraPos.y -300;
    m_vDir = m_vDir.Normalized();
    m_vForce = m_vDir;
}

Bullet::Bullet()
    /*: m_vForce(m_vDir)*/
{
}
