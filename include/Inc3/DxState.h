#pragma once
#include "TStd.h"
class DxState
{
public:
	static ID3D11SamplerState* g_pDefaultSS;
public:
	static bool SetState(ID3D11Device* _pd3dDevice);
	static bool Release();
};

