#pragma once
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include "TWindow.h"
#include <d3d11.h>

class Sample : public TWindow
{
public:
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��
	// DX�� I�� ���� I D3D11 Device
	ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)		// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���

	IDXGIFactory* m_pGIFactory = nullptr;		// swapChain ����� ���ػ���
	IDXGISwapChain* m_pSwapChain = nullptr;		

	ID3D11RenderTargetView* m_pRTV = nullptr;	// ����۸� ���� ����Ÿ�ٺ並 �����Ѵ�.

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
};

