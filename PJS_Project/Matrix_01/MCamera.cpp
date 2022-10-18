#include "MCamera.h"

void MCamera::CreateViewMatrix(Vector3D _vEye, Vector3D _vAt, Vector3D _vUp)
{
	m_vCameraPos = _vEye;
	m_vTarget = _vAt;
	m_vUp = _vUp;
	
}

void MCamera::CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio)
{

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

	return true;
}
