#pragma once
#include "BObject.h"
#include "Vector.h"
typedef std::vector<Rect> RECT_ARRAY;
class Object2D : public BObject
{
public:
	POINT m_ptImageSize;
	Rect m_rtInit;
	Rect m_rtUV;
	Rect m_rtCollision;
	Vector2D m_vCenterPoint;
	Vector2D m_vPosition;
	Vector2D m_vDir;
	Vector2D m_vForce;
	float	 m_fSpeed;
	float	 m_fMass;
	W_STR					m_szName;					// 오브젝트 이름
	UINT					m_Iindex;					// 오브젝트 인덱스
public:
	RECT_ARRAY				m_uvArray;					// 오브젝트 좌표 모음 배열 (텍스트 좌표 파일 보관)
public:
	Vector2D				m_vDrawPos;					// NDC좌표 오브젝트 포지션
	Vector2D				m_vDrawSize;				// NDC좌표 오브젝트 사이즈
public:
	virtual bool Frame() override;
	virtual void SetDirection(Vector2D _dir);
	void SetRect(Rect _Pos);
	void SetPosition(Vector2D _pos);
	void UpdateVertexBuffer();
};

