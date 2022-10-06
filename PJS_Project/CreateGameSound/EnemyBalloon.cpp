#include "EnemyBalloon.h"

bool EnemyBalloon::Init()
{
    if (m_iHp < 2)
    {
        m_vPosition = { 2310, 1050.f};
    }
    else
    {
        m_vPosition = { 2000, 1050.f };
    }
    m_iIndex = m_iHp;
    SetCameraSize({ 800,600 });
    m_fSpeed = 100.0f;
    return true;
}

bool EnemyBalloon::Frame()
{
    Move();
    SetPosition(m_vPosition, m_vCameraPos);
    return true;
}

bool EnemyBalloon::Render()
{
    Object2D::Render();
    return true;
}

bool EnemyBalloon::Move()
{
    Vector2D _vPos;
    _vPos = m_vPosition;
    if (m_iIndex < 2)
    {
        if (m_vPosition.y >= 1038.f && MoveCheck == true)
        {
            _vPos.y += 1.0f * 100 * I_Timer.m_fDeltaTime;
            if (m_vPosition.y >= 1400.f)
                MoveCheck = false;
        }
        if (m_vPosition.y <= 1403.f && MoveCheck == false)
        {
            _vPos.y += -1.0f * 100 * I_Timer.m_fDeltaTime;
            if (m_vPosition.y <= 1040.f)
                MoveCheck = true;
        }
    }
    if (m_iIndex >= 2)
    {
        if (m_vPosition.y >= 1038.f && MoveCheck == true)
        {
            _vPos.y += 1.0f * 100 * I_Timer.m_fDeltaTime;
            if (m_vPosition.y >= 1500.f)
                MoveCheck = false;
        }
        if (m_vPosition.y <= 1503.f && MoveCheck == false)
        {
            _vPos.y += -1.0f * 100 * I_Timer.m_fDeltaTime;
            if (m_vPosition.y <= 1040.f)
                MoveCheck = true;
        }
    }
    m_vPosition = _vPos;
    return true;
}
