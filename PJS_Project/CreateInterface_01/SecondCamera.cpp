#include "SecondCamera.h"

bool SecondCamera::Init()
{
	m_pInterface = new Interface;
	m_pInterface->SetDevice(m_p3dDevice, m_pImmediateContext);
	m_pInterface->Create(L"../../shader/DefaultShader.txt", L"../../data/Scope.png");
	m_pInterface->SetRect({ 0,0,800,599 });
	m_pInterface->SetPosition({ 0,0 });
	SetCameraSize({ 800,600 });
	return true;
}

bool SecondCamera::Frame()
{
	Move();
	SetPosition(m_vPosition, m_vCameraPos);
	return true;
}

bool SecondCamera::Move()
{
	Vector2D _vScPos = m_vPosition;
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		_vScPos.y += -1.0f * 200.f * I_Timer.m_fDeltaTime;
	}
	if (I_Input.GetKey('A') == KEY_HOLD)
	{
		_vScPos.x += -1.0f * 200.f * I_Timer.m_fDeltaTime;
	}
	if (I_Input.GetKey('S') == KEY_HOLD)
	{
		_vScPos.y += 1.0f * 200.f * I_Timer.m_fDeltaTime;
	}
	if (I_Input.GetKey('D') == KEY_HOLD)
	{
		_vScPos.x += 1.0f * 200.f * I_Timer.m_fDeltaTime;
	}
	m_vPosition = _vScPos;
	return true;
}

bool SecondCamera::Render()
{
	m_pInterface->Render();
	return true;
}

bool SecondCamera::Release()
{
	m_pInterface->Release();
	delete m_pInterface;
	Object2D::Release();
	return true;
}