#pragma once
#include "Scene.h"
class SceneGameover : public Scene
{
public:
	BObject* m_pTitleMap;
	//std::vector<Button*> m_pBtnList;
	//Interface m_iInterface;
	TSound* m_pWallSound;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:

};

