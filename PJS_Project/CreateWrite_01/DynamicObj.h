#pragma once
#include "TStd.h"
#include "BaseObject.h"
#include "Vector.h"
class DynamicObj : public BaseObject
{
public:
	POINT		m_ptImageSize;
	Rect		m_rtInit;
	Rect		m_rtUV;
	Vector2D	m_vPos;
	Vector2D	m_vDir;
	float		m_fSpeed;
private:
	Vector2D	m_vDrawPos;
	Vector2D	m_vDrawSize;
public:
	bool Frame()override;
	void SetRect(Rect _rt);
	void SetDirection();
	void SetPosition(Vector2D _vec);
	void UpdateVertexBuffer();
};

