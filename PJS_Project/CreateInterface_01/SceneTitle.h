#pragma once
#include "Scene.h"
#include "Interface.h"
class SceneTitle : public Scene
{
public:
	BObject* m_pTitleMap;
	//std::vector<Button*> m_pBtnList;
	Interface m_iInterface;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	// bool SetUI();
};

