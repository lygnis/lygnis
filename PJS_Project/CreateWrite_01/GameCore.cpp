#include "GameCore.h"

bool GameCore::Init()
{
	m_pDevice = new DxDevice;
	m_pObject = new BaseObject;
	if (false == m_pDevice->Init())
		return false;
	/*if (false == m_pObject->Create(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext, L"D:/C_PRJ/data/popup_normal.bmp", L"D:/C_PRJ/shader/DefaultShader.txt"))
		return false;*/
	m_pMap = new BaseObject;
	m_pMap->Create(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext, L"D:/Git_PJS_C/data/1KGCABK.bmp", L"D:/Git_PJS_C/shader/DefaultShader.txt");
	m_pUser = new DynamicObj;
	m_pUser->Create(m_pDevice->m_p3dDevice, m_pDevice->m_pImmediateContext, L"D:/Git_PJS_C/data/Fortress.png", L"D:/Git_PJS_C/shader/DefaultShader.txt");
	m_pUser->m_fSpeed = 300.0f;
	m_pUser->SetRect({ 40,148,32,32 });
	m_pUser->SetPosition({ g_rtClient.right / 2.0f, g_rtClient.bottom - 100.0f });
	m_wWrite.Init();
	m_pDevice->m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
	m_wWrite.Set(m_pBackBuffer);
	I_Input.Init();
	m_tTimer.Init();
	//m_wWrite.Init();
	return true;
}

bool GameCore::Frame()
{
	m_tTimer.Frame();
	I_Input.Frame();
	POINT ptPos = m_tKeyInput.m_ptPos;
	//m_pMap->Frame();
	m_pUser->Frame();
	/*if (I_Input.GetKey('W') == KeyState::KEY_HOLD)
	{
		
	}
	if (I_Input.GetKey(VK_LBUTTON) == KeyState::KEY_HOLD)
	{
		INT k = 0;
	}*/

	return true;
}
bool GameCore::Render()
{
	m_pDevice->PreRender();
	m_tTimer.Render();
	/*if (I_Input.GetKey('W') == KeyState::KEY_HOLD)
	{
		m_pObject->Render();
	}*/
	m_pMap->Render();
	m_pUser->Render();
	m_wWrite.m_szDefaultText = m_tTimer.m_szTimer;
	m_wWrite.Render();
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
	delete m_pMap;
	delete m_pUser;
	return true;
}
