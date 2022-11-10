#pragma once
#include "TStd.h"
#pragma comment(lib, "DirectXTK.lib")
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h" 
class Texture
{
public:
	//ID3D11Device* m_p3dDevice = nullptr;		// 1번 디바이스 획득 (디바이스 객체)		// 소멸할때 쓰레기 값일 수도 있으니 Nullptr로 설정
	//ID3D11DeviceContext* m_pImmediateContext = nullptr;		// 즉시
public:
	ID3D11Resource* m_pTexture;
	ID3D11ShaderResourceView* m_pSrvTexture;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	HRESULT Load(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _fileName);
};

