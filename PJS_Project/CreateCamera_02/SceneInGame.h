#pragma once
#include "Scene.h"
#include "MapObject.h"
#include "Player.h"

class SceneInGame : public Scene
{
public:
	Player* m_pPlayer;
	MapObject* m_pMapObject;
	Vector2D   m_vCamera;

private:
	float m_fCurrTime;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	bool SetPlayer();
	bool SetMap();
};

