#include "SceneTitle.h"

bool SceneTitle::Init()
{
	bool hr;
	m_pTitleMap = new BObject;
	hr = m_pTitleMap->SetDevice(m_pd3dDevice, m_pImmediateContext);
	if (hr == false) { return false; }
	hr = m_pTitleMap->Create(L"../../shader/DefaultShader.txt", L"D:/Git_PJS_C/data/1KGCABK.bmp");
	if (hr == false) { return false; }
	//SetUI();
	return true;
}

bool SceneTitle::Frame()
{
	m_pTitleMap->Frame();
	//m_iInterface.m_pBtnList[0]->Frame();
	return true;
}

bool SceneTitle::Render()
{
	m_pTitleMap->Render();
	//m_iInterface.m_pBtnList[0]->Render();
	return true;
}

bool SceneTitle::Release()
{
	m_pTitleMap->Release();
	delete m_pTitleMap;
	return true;
}

//bool SceneTitle::SetUI()
//{
//	Button* newBtn = new Button;
//	newBtn->SetDevice(m_pd3dDevice, m_pImmediateContext);
//	newBtn->Create(L"../../shader/DefaultShader.txt", L"../../data/png/main_start_nor.bmp");
//	newBtn->SetRect({ 0.0f, 0.0f, 334, 82 });
//	newBtn->SetPosition({ 400,450 });
//	m_iInterface.m_pBtnList.push_back(newBtn);
//	Button* newBtn1 = new Button;
//	newBtn->SetDevice(m_pd3dDevice, m_pImmediateContext);
//	newBtn->Create(L"../../shader/DefaultShader.txt", L"../../data/png/main_start_pus.bmp");
//	newBtn->SetRect({ 0.0f, 0.0f, 334, 82 });
//	newBtn->SetPosition({ 400,450 });
//	m_iInterface.m_pBtnList.push_back(newBtn);
//	Button* newBtn2 = new Button;
//	newBtn->SetDevice(m_pd3dDevice, m_pImmediateContext);
//	newBtn->Create(L"../../shader/DefaultShader.txt", L"../../data/png/main_start_sel.bmp");
//	newBtn->SetRect({ 0.0f, 0.0f, 334, 82 });
//	newBtn->SetPosition({ 400,450 });
//	m_iInterface.m_pBtnList.push_back(newBtn);
//	Button* newBtn3 = new Button;
//	newBtn->SetDevice(m_pd3dDevice, m_pImmediateContext);
//	newBtn->Create(L"../../shader/DefaultShader.txt", L"../../data/png/main_start_dis.bmp");
//	newBtn->SetRect({ 0.0f, 0.0f, 334, 82 });
//
//	newBtn->SetPosition({ 400,450 });
//	m_iInterface.m_pBtnList.push_back(newBtn);
//	return true;
//}
