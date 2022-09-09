#pragma once
#include "TStd.h"
#include"ShaderManager.h"
class Shader
{
public:
	
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT LoadShader(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _sFileName) ;
};

