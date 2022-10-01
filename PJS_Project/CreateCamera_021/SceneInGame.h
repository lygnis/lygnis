#pragma once
#include "Scene.h"
#include "MapObject.h"
#include "Player.h"
#include "Coordinate.h"
class SceneInGame : public Scene
{
public:
	Player* m_pPlayer;
	MapObject* m_pMapObject;
	Vector2D   m_vCamera;
	Writer*     m_wWriter;
	IDXGISurface1* m_pBackBuffer;
private:
	float m_fCurrTime;
	float m_fGravity = 50.0f;
	bool  m_bGravityUse = true;
public:
	std::list<MapObject*> GroundObjList;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	bool SetPlayer();
	bool SetMap();
	bool SetTile();
	bool CheckCollision();
	bool PlayerCollision();
};

