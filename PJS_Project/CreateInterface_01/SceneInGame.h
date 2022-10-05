#pragma once
#include "Scene.h"
#include "MapObject.h"
#include "Player.h"
#include "EnemyBalloon.h"
#include "ItemBox.h"
#include "Coordinate.h"
#include "Interface.h"
#include "EnemyPig.h"
#include<deque>
class SceneInGame : public Scene
{
public:
	Player* m_pPlayer;
	//EnemyBalloon* m_pBalloon;
	MapObject* m_pMapObject;
	Vector2D   m_vCamera;
	//Writer*     m_wWriter;
	IDXGISurface1*	m_pBackBuffer;
	Interface*		m_pInterface;
	Interface*		m_pMissileUI;
	GameClear		m_bClear = GAME_NONE;
private:
	int   m_iScore;
	float m_fCurrTime;
	float m_fGravity = 50.0f;
	bool  m_bGravityUse = true;
public:
	std::list<MapObject*> GroundObjList;
	std::deque<Interface*> m_pMissileUiList;
	std::vector<Interface*> m_pBarList;
	std::list<EnemyBalloon*>	m_pBalloonObjList;
	std::list<ItemBox*>			m_pItemBoxList;
	std::list<EnemyPig*>		m_pEnemyList;
public:
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
public:
	bool SetObject();
	bool SetPlayer();
	bool SetMap();
	bool SetTile();
	bool SetUI();
	bool CheckCollision();
	bool PlayerCollision();
	GameClear ClearCheck();
};

