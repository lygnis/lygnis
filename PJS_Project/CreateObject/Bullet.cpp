#include "Bullet.h"

bool Bullet::Frame()
{
    Vector2D _vPos = m_vPosition;
    m_fSpeed = 500.0f;
    _vPos.x += m_vDir.x* m_fSpeed * I_Timer.m_fDeltaTime;
    _vPos.y += m_vDir.y * m_fSpeed * I_Timer.m_fDeltaTime;

    SetPosition(_vPos);
    if (m_vDrawPos.x > 1.0f|| m_vDrawPos.y > 1.0f)
    {
        this->Release();
        delete this;
        return true;
    }
    if (m_vDrawPos.x < -1.0f|| m_vDrawPos.y < -1.0f)
    {
        this->Release();
        delete this;
        return true;
    }
    return true;
}

void Bullet::GetMousePosition(POINT _vec, Vector2D _center)
{
    m_vDir.x = _vec.x - _center.x;
    m_vDir.y = _vec.y - _center.y;
    m_vDir = m_vDir.Normalized();
}
