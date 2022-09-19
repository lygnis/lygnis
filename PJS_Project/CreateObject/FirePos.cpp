#include "FirePos.h"


Bullet* FirePos::MakeBullet(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, Vector2D _firePos)
{
	Bullet* bullet = new Bullet;
	bullet->SetDevice(_p3dDevice, _pImmediateContext);
	bullet->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/msadv_talltank.gif");
	bullet->SetRect({ 4,321,16,14 });
	bullet->SetPosition(_firePos);
	bullet->GetMousePosition(I_Input.m_pMpos, _firePos);
	return bullet;
}
