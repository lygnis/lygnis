#pragma once
#include "TStd.h"
#pragma comment(lib, "DirectXTK.lib")
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h" 
class Texture
{
public:
	//ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)		// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	//ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���
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

