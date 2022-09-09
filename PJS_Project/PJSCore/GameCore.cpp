#include "GameCore.h"

bool GameCore::CoreInit()
{
	//m_pWindow = new TWindow;
	m_pDevice = new DxDevice;
	m_pDevice->Init();
	m_wWriter.Init();
	m_tTimer.Init();
	m_iInput.Init();
	m_pDevice->m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
	m_wWriter.Set(m_pBackBuffer);
	return Init();
}

bool GameCore::CoreFrame()
{
	m_tTimer.Frame();
	m_iInput.Frame();
	return Frame();
}
bool GameCore::CoreRender()
{
	m_pDevice->PreRender();
	Render();
	m_tTimer.Render();
	m_wWriter.m_szOutputText = m_tTimer.m_szTimeNFps;
	m_wWriter.Render();
	m_pDevice->PostRender();
	return true;
}
bool GameCore::CoreRelease()
{
	Release();
	m_pDevice->Release();
	m_wWriter.Release();
	m_tTimer.Release();
	m_iInput.Release();
	if (m_pBackBuffer)m_pBackBuffer->Release();
	delete m_pDevice;
	delete m_pWindow;
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
			return false;
		}
	}
	CoreRelease();
	return true;
}

