#pragma once
#include "Object2D.h"
typedef std::vector<Rect> RECT_ARRAY;
class Sprite : public Object2D
{
public:
	W_STR					m_szName;
	UINT					m_Iindex;
public:
	RECT_ARRAY				m_uvArray;
	//std::vector<Sprite*>	m_pChild;
	Rect					m_rtCollision;
public:
	void SetPosition(Vector2D _pos) override;
	void SetPosition(Vector2D _pos, Vector2D _vCamera) override;
	HRESULT Load(const WCHAR* _filName);
};

