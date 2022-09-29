#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
public:
	BObject* m_pTitleMap;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

