#pragma once
#include "TStd.h"
//#include"ShaderManager.h"
class Shader
{
public:
	// 1. 디바이스 필요
	ID3D11Device* m_p3dDevice = nullptr;		// 1번 디바이스 획득 (디바이스 객체)
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// 즉시
	// 2. 버텍스 픽셀 쉐이더를 갖고온다
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT LoadShader(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _sFileName) ;
};

