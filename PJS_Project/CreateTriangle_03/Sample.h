#pragma once
#include "TWindow.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include <d3d11.h>
#include "DxDevice.h"
struct SimpleVertex
{			// ������ ��ġ
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
	float a;
};

class Sample : public DxDevice
{
public:
	//DxDevice m_dxDevice;			// ����� ���ؼ��� �����ϴ�

	ID3D11Buffer* m_pVertexBuffer;			// ���ؽ� ���� ����
	// ������� ���۸� IA�� �Ѱ���� �Ѵ�.
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVSCode = nullptr;
	ID3DBlob* m_pPSCode = nullptr;
	
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateShader();
public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����

};

