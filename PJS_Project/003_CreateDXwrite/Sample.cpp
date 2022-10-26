#include "Sample.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Sample gSample;
	if (!gSample.InitWindow(hInstance, nCmdShow, L"CreateWindow"))
	{
		MessageBox(0, _T("CreateWindow  초기화 실패"), _T("Fatal error"), MB_OK);
		return 0;
	}
	ShowCursor(TRUE);
	gSample.Run();
	return 1;
}

bool Sample::Init()
{
	DxDevice::Init();
	I_Timer.Init();
	I_Timer.Start();
	IDXGISurface* pBackBuffer;
	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&pBackBuffer);
	m_Font.Set( pBackBuffer);
	if (pBackBuffer) pBackBuffer->Release();
	return true;
}
bool Sample::Frame()
{
	I_Timer.Frame();
	return true;
}
bool Sample::Render()
{
	DxDevice::PreRender();
	I_Timer.Render();
	m_Font.Begin();
	m_Font.m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_Font.m_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	RECT rc1 = { 0,0, m_iWindowWidth, m_iWindowHeight };
	m_Font.DrawText(1,1, I_Timer.m_szTimeNFps, D2D1::ColorF(1, 1, 1, 0.5));
	m_Font.End();
	DxDevice::PostRender();
	return true;
}
bool Sample::Release()
{
	I_Timer.Stop();
	DxDevice::Release();
	I_Timer.Release();
	m_Font.Release();
	return true;
}
