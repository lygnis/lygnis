#include "ThirdPersonCamera.h"

bool ThirdPersonCamera::Frame()
{
    if (Input::get()->GetKey(VK_RBUTTON) == KEY_HOLD)
    {
        m_fYaw += Input::get()->m_pOffset.x * 0.002;
        m_fPitch += Input::get()->m_pOffset.y * 0.002;
        // X 축 회전을 통해 상하가 반전되지 않게 방지한다.
        if (m_fPitch >= 1.57f)
            m_fPitch = 1.57f;
        else if (m_fPitch <= -1.57f)
            m_fPitch = -1.57f;
    }
    if (Input::get()->GetKey('W') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
    }
    if (Input::get()->GetKey('S') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
    }
    if (Input::get()->GetKey('D') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
    }
    if (Input::get()->GetKey('A') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
    }
    if (Input::get()->GetKey('Q') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
    }
    if (Input::get()->GetKey('E') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
    }

    _matWorld.Identity;
    //m_vCameraPos = target_pos_;
    //TVector3 _pos = _matWorld.Backward() * (-target_distance_);
    TVector3 _vPos = m_vCameraPos;

    ////////////////////////////////////////////////////////

    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matProj;
    TBASIS_EX::TQuaternion qRotation;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, m_fYaw, m_fPitch, m_fRoll);
    TBASIS_EX::D3DXMatrixAffineTransformation(&_matWorld, 1.0f, NULL, &qRotation, &_vPos);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &_matWorld);

    m_matView = matView;
    Update();
    return true;
}

bool ThirdPersonCamera::Update()
{
    m_vRight.x = m_matView._11;
    m_vRight.y = m_matView._21;
    m_vRight.z = m_matView._31;

    m_vUp.x = m_matView._12;
    m_vUp.y = m_matView._22;
    m_vUp.z = m_matView._32;

    m_vLook.x = m_matView._13;
    m_vLook.y = m_matView._23;
    m_vLook.z = m_matView._33;

    m_vRight.Normalize();
    m_vUp.Normalize();
    m_vLook.Normalize();

    return true;
}
