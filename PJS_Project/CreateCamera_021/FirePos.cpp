#include "FirePos.h"


Bullet* FirePos::MakeBullet(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, Vector2D _firePos, Vector2D _m_vCameraPos)
{
	Bullet* bullet = new Bullet;
	bullet->SetDevice(_p3dDevice, _pImmediateContext);
	bullet->Create(L"../../shader/DefaultShader.txt", L"D:/Git_PJS_C/data/msadv_talltank.gif");
	bullet->SetRect({ 125,322,14,14 });
	bullet->SetPosition(_firePos);
	bullet->GetMousePosition(I_Input.m_pMpos, _firePos , _m_vCameraPos);
	return bullet;
}
