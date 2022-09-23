#pragma once
#include "GameCore.h"
#include "DxState.h"
#include "SceneInGame.h"
#include "SceneTitle.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


class Player;
class SpriteManager;

class Sample : public GameCore
{
public:
	SceneTitle*		m_pStartScene = nullptr;
	SceneInGame*	m_pGameScene = nullptr;
	Scene*			m_pCurrScene = nullptr;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

