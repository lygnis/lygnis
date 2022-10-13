#include "GameCore.h"

bool GameCore::CoreInit()
{
	//m_pWindow = new TWindow;
	DxDevice::Init();
	m_wWriter.Init();
	I_Timer.Init();
	I_Input.Init();
	//m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&m_pBackBuffer);
	IDXGISurface1* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&pBackBuffer);
	m_wWriter.Set(pBackBuffer);
	pBackBuffer->Release();
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
	DxDevice::PreRender();
	Render();
	I_Timer.Render();
	m_wWriter.m_szOutputText = I_Timer.m_szTimeNFps;
	m_wWriter.Render();
	DxDevice::PostRender();
	return true;
}
bool GameCore::CoreRelease()
{
	DxDevice::Release();
	m_wWriter.Release();
	I_Timer.Release();
	I_Input.Release();

	Release();
	return true;
}

bool GameCore::SetWindow(HINSTANCE hInstance, const WCHAR* _prjName, UINT iWidth, UINT iHeight)
{
	m_bGameRun = TWindow::SetWindow(hInstance, _prjName, iWidth, iHeight);
	return m_bGameRun;
}
HRESULT GameCore::CreateDXResource()
{
	m_wWriter.Init();
	IDXGISurface1* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&pBackBuffer);
	m_wWriter.Set(pBackBuffer);
	pBackBuffer->Release();
	return S_OK;
}
HRESULT GameCore::DeleteDXResource()
{
	m_wWriter.Release();
	m_wWriter.DeleteDXResource();
	return S_OK;
}
bool GameCore::Run()
{

	CoreInit();
	while (m_bGameRun)
	{
		if (TWindow::Run() == true)
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

