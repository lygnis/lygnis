#include "DebugCamera.h"

bool DebugCamera::Frame()
{
    if (I_Input.GetKey(VK_RBUTTON)==KEY_HOLD)
    {
        m_fYaw += I_Input.m_pOffset.x * 0.002;
        m_fPitch += I_Input.m_pOffset.y * 0.002;
    }
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos += _vec;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vLook * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos -= _vec;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos += _vec;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vRight * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos -= _vec;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('Q') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos += _vec;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('E') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = m_vUp * 10 * I_Timer.m_fDeltaTime;
        Vector3D _vec;
        _vec.x = _v.x;
        _vec.y = _v.y;
        _vec.z = _v.z;
        m_vCameraPos -= _vec;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }
    
    TBASIS_EX::TVector3 _vPos;
    _vPos.x = m_vCameraPos.x;
    _vPos.y = m_vCameraPos.y;
    _vPos.z = m_vCameraPos.z;
    ////////////////////////////////////////////////////////
    TBASIS_EX::TMatrix matWorld;
    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matProj;
    TBASIS_EX::TQuaternion qRotation;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, m_fYaw, m_fPitch, m_fRoll);
    TBASIS_EX::D3DXMatrixAffineTransformation(&matWorld, 1.0f, NULL, &qRotation, &_vPos);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &matWorld);
    m_matView = *((MyMatrix4X4*)&matView);

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

    m_vFrustum.CreateFrustum(&m_matView, &m_matProj);
    return true;
}
