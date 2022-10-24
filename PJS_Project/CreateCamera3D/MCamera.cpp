#include "MCamera.h"

void MCamera::CreateViewMatrix(Vector3D _vEye, Vector3D _vAt, Vector3D _vUp)
{
	m_vCameraPos = _vEye;
	m_vTarget = _vAt;
	m_vUp = _vUp;
    m_matView.ViewLookAt(_vEye, _vAt, _vUp);
}

void MCamera::CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio)
{
    m_fNear = _fNear;
    m_fFar = _fFar;
    m_fFovY = fFovY;
    m_fAspectRatio = fAspecRatio;
    // 원근 투영
    m_matProj.PerspectiveFovLH(_fNear, _fFar, fFovY, fAspecRatio);
    //m_matProj.OrthoLH(m_matProj,800, 600, 0.0f, 100.0f);
    //m_matProj.OrthoOffCenterLH(m_matProj, -400, 400, -300, 300,0.0f, 100.0f);
}

bool MCamera::Frame()
{
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        m_vCameraPos.z += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        m_vCameraPos.z -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        m_vCameraPos.x -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        m_vCameraPos.x += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('Q') == KEY_HOLD)
    {
        m_vCameraPos.y += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('E') == KEY_HOLD)
    {
        m_vCameraPos.y -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }

    m_matView.ViewLookAt(m_vCameraPos, m_vTarget, m_vUp);
	return true;
}
