#pragma once
#include "Vector.h"
#include "TStd.h"
#include "Bullet.h"
class FirePos 
{
public:
	Bullet* MakeBullet(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, Vector2D _firePos, Vector2D _m_vCameraPos);
};

