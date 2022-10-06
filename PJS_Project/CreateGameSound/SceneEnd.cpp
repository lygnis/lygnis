#include "SceneEnd.h"
bool SceneEnd::Init()
{
	bool hr;
	m_pTitleMap = new BObject;
	hr = m_pTitleMap->SetDevice(m_pd3dDevice, m_pImmediateContext);
	if (hr == false) { return false; }
	hr = m_pTitleMap->Create(L"../../shader/DefaultShader.txt", L"../../data/GameClearScene.png");
	if (hr == false) { return false; }
	I_Sound.Init();
	I_Sound.LoadAll(L"../../data/sound/");
	m_pWallSound = I_Sound.GetPtr(L"MissionClear.mp3");
	//SetUI();
	return true;
}

bool SceneEnd::Frame()
{
	I_Sound.Frame();
	m_pTitleMap->Frame();
	//m_iInterface.m_pBtnList[0]->Frame();
	return true;
}

bool SceneEnd::Render()
{
	m_pTitleMap->Render();
	//m_iInterface.m_pBtnList[0]->Render();
	return true;
}

bool SceneEnd::Release()
{
	m_pTitleMap->Release();
	delete m_pTitleMap;
	return true;
}