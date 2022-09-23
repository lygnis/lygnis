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
	W_STR					m_szName;					// ������Ʈ �̸�
	UINT					m_Iindex;					// ������Ʈ �ε���
public:
	RECT_ARRAY				m_uvArray;					// ������Ʈ ��ǥ ���� �迭 (�ؽ�Ʈ ��ǥ ���� ����)
public:
	Vector2D				m_vDrawPos;					// NDC��ǥ ������Ʈ ������
	Vector2D				m_vDrawSize;				// NDC��ǥ ������Ʈ ������
public:
	virtual bool Frame() override;
	virtual void SetDirection(Vector2D _dir);
	void SetRect(Rect _Pos);
	void SetPosition(Vector2D _pos);
	void UpdateVertexBuffer();
};

