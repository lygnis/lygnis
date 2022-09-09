#pragma once
#include "TStd.h"
#include "TWindow.h"
class DxDevice : public TWindow
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

	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
private:
	bool		TPreRender();
	bool        TPostRender();
	bool		TInit()override; // �ʱ�ȭ
	bool		TFrame()override;// �ǽð� ���
	bool		TRender()override;// �ǽð� ������
	bool		TRelease()override;// �Ҹ� �� ����

};

