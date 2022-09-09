#include "GameCore.h"

bool GameCore::Init()
{
	m_pDevice = new DxDevice;
	m_pObject = new BaseObject;
	if (false == m_pDevice->Init())
		return false;
	if (false == m_pObject->Create(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext, L"D:/C_PRJ/data/popup_normal.bmp", L"D:/C_PRJ/shader/DefaultShader.txt"))
		return false;
	I_Input.Init();
	m_tTimer.Init();

	return true;
}

bool GameCore::Frame()
{
	m_tTimer.Frame();
	I_Input.Frame();
	POINT ptPos = m_tKeyInput.m_ptPos;
	if (I_Input.GetKey('W') == KeyState::KEY_HOLD)
	{
		
	}
	if (I_Input.GetKey(VK_LBUTTON) == KeyState::KEY_HOLD)
	{
		INT k = 0;
	}

	return true;
}
bool GameCore::Render()
{
	m_pDevice->PreRender();
	m_tTimer.Render();
	if (I_Input.GetKey('W') == KeyState::KEY_HOLD)
	{
		m_pObject->Render();
	}
	m_pDevice->PostRender();
	return true;
}
bool GameCore::Release()
{
	if(m_pDevice)
		m_pDevice->Release();
	if(m_pObject)
		m_pObject->Release();
	if (m_pWindow)
		m_pWindow->Release();
	return true;
}
