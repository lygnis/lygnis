#pragma once
#include "BObject.h"
#include "Vector.h"
class Object2D : public BObject
{
public:
	POINT m_ptImageSize;
	Rect m_rtInit;
	Rect m_rtUV;
	Vector2D m_vCenterPoint;
	Vector2D m_vPosition;
	Vector2D m_vDir;
	Vector2D m_vForce;
	float	 m_fSpeed;
	float	 m_fMass;
public:
	Vector2D m_vDrawPos;
	Vector2D m_vDrawSize;
public:
	virtual bool Frame() override;
	virtual void SetDirection(Vector2D _dir);
	void SetRect(Rect _Pos);
	void SetPosition(Vector2D _pos);
	void UpdateVertexBuffer();
};

