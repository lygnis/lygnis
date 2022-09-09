#pragma once
#include "TStd.h"
#include "TWindow.h"

class DxDevice
{
public:
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��
	// DX�� I�� ���� I D3D11 Device
	ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)		// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���

	IDXGIFactory* m_pGIFactory = nullptr;		// swapChain ����� ���ػ���
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;	// ����۸� ���� ����Ÿ�ٺ並 �����Ѵ�.

private:
	// 1) ����̽� ����
	HRESULT CreateDevice();
	// 2) ���丮 ���� (DXGI �� �ϴ� ����, ��� )
	HRESULT CreateDXGIDevice();
	// 3) ���� ü�� ����
	HRESULT CreateSwapChain();
	// 4) ����Ÿ�ٺ� ����
	HRESULT CreateRenderTargetView();
	// 5) ����Ʈ ����
	void CreateViewPort();
public:
	bool		PreRender();
	bool        PostRender();
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
//	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����

};
//#define I_Device DxDevice::GetInstance()
