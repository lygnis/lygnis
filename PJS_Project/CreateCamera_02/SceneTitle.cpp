#include "SceneTitle.h"

bool SceneTitle::Init()
{
	bool hr;
	m_pTitleMap = new BObject;
	hr = m_pTitleMap->SetDevice(m_pd3dDevice, m_pImmediateContext);
	if (hr == false) { return false; }
	hr = m_pTitleMap->Create(L"../../shader/DefaultShader.txt", L"D:/Git_PJS_C/data/1KGCABK.bmp");
	if (hr == false) { return false; }
	return true;
}

bool SceneTitle::Frame()
{
	m_pTitleMap->Frame();
	return true;
}

bool SceneTitle::Render()
{
	m_pTitleMap->Render();
	return true;
}

bool SceneTitle::Release()
{
	m_pTitleMap->Release();
	delete m_pTitleMap;
	return true;
}
