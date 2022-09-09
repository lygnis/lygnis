#pragma once
#include "TStd.h"
//#include"ShaderManager.h"
class Shader
{
public:
	// 1. ����̽� �ʿ�
	ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���
	// 2. ���ؽ� �ȼ� ���̴��� ����´�
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

