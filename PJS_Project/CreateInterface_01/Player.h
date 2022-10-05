#pragma once
#include "FirePos.h"
#include "Bullet.h"
#include "Efeect.h"
#include <list>
#include "Sprite.h"
#include "SecondCamera.h"
class Bullet;
enum PlayerState
{
	NONE=0,
	IDLE,
	FIRE,
	STAY,
	LOSE,
};

class Player : public Object2D
{
private:
	FirePos					m_bFirePos;
	float					m_fFireCoolTime = 0.1f;
	float					m_fCurrTime;
	float					m_fBulletPower = 0;
	float					m_fChargingTime = 0.0f;
	float					m_fIdleTime;
	bool					m_bEffect = false;
	float					m_fEnergy = 6.0f;
	PlayerState				m_iState = NONE;
	bool					m_bFire = false;
	bool					m_fChangeCameraTime;
	Vector2D				m_vSecondCamera;
public:
	Sprite*					m_pSprite = nullptr;
	UINT					m_iIndex = 0;
	UINT					m_iMaxIndex = 1;
	float					m_fEffectTimer = 0.0f;
	float					m_fStep = 1.0f;
	Vector2D				m_vCurrCameraPos;
	bool					m_bCollsionCheck = true;
	float					m_fFireGage;
	float					m_fMoveEnergyGage;
	int						m_iMissileCount;
	SecondCamera*			m_pSecondCamera;
public:
	std::list<Bullet*>		m_pBulletList;
	std::list<Efeect*>		m_pEffectList;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool SecondMove();
	bool Move();
	bool Fire();
	bool AddEffect(Vector2D _pos);
	bool Update();
	void AnimState();
	bool FireUpdate(bool _fire);
	PlayerState TankIdle();
	PlayerState TankFire();
	PlayerState TankStay();
	PlayerState TankLose();
	PlayerState TankMove();
};

