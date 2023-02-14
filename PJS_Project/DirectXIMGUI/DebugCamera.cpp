#include "DebugCamera.h"

bool DebugCamera::Frame()
{
    if (Input::get()->GetKey(VK_RBUTTON)==KEY_HOLD)
    {
        m_fYaw += Input::get()->m_pOffset.x * 0.002;
        m_fPitch += Input::get()->m_pOffset.y * 0.002;
    }
    if (Input::get()->GetKey('W') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('S') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('D') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('A') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('Q') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('E') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }
    
    TBASIS_EX::TVector3 _vPos;
    _vPos.x = m_vCameraPos.x;
    _vPos.y = m_vCameraPos.y;
    _vPos.z = m_vCameraPos.z;
    ////////////////////////////////////////////////////////

    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matProj;
    TBASIS_EX::TQuaternion qRotation;
    _matWorld.Identity;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, m_fYaw, m_fPitch, m_fRoll);
    TBASIS_EX::D3DXMatrixAffineTransformation(&_matWorld, 1.0f, NULL, &qRotation, &_vPos);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &_matWorld);
    m_matView = matView;

    TVector3 vEye = TVector3(0.0f, 0.0f, -100.0f);
    TVector3 vAt = TVector3(0.0f, 0.0f, 100.0f);
    TVector3 vUp(0.0f, 1.0f, 0.0f);
    mat_ui_view_ = TMatrix::CreateLookAt(vEye, vAt, vUp);
    Update();
    return true;
}

bool DebugCamera::Update()
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
