#include "GameCore.h"

bool GameCore::CoreInit()
{
	//m_pWindow = new TWindow;
	m_pDevice = new DxDevice;
	m_pDevice->Init();
	m_wWriter.Init();
	I_Timer.Init();
	I_Input.Init();
	m_pDevice->m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
	m_wWriter.Set(m_pBackBuffer);
	return Init();
}

bool GameCore::CoreFrame()
{
	I_Timer.Frame();
	I_Input.Frame();
	return Frame();
}
bool GameCore::CoreRender()
{
	m_pDevice->PreRender();
	Render();
	I_Timer.Render();
	m_wWriter.m_szOutputText = I_Timer.m_szTimeNFps;
	m_wWriter.Render();
	m_pDevice->PostRender();
	return true;
}
bool GameCore::CoreRelease()
{
	m_pDevice->Release();
	m_wWriter.Release();
	I_Timer.Release();
	I_Input.Release();
	if (m_pBackBuffer)m_pBackBuffer->Release();
	delete m_pDevice;
	delete m_pWindow;

	Release();
	return true;
}

bool GameCore::SetWindow(HINSTANCE hInstance, const WCHAR* _prjName, UINT iWidth, UINT iHeight)
{
	m_pWindow = new TWindow;
	m_bGameRun = m_pWindow->SetWindow(hInstance, _prjName, iWidth, iHeight);
	return m_bGameRun;
}
bool GameCore::Run()
{
	
	CoreInit();
	while (m_bGameRun)
	{
		if (m_pWindow->Run() == true)
		{
			CoreFrame();
			CoreRender();
		}
		else
		{
			CoreRelease();
			return false;
		}
	}
	return true;
}

