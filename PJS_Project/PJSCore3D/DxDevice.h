#pragma once
#include "TWindow.h"
#include "DxState.h"
class DxDevice : public TWindow
{
	// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	// �������̽� -> �ϵ���� ���� ���� -> ȹ��
public:
	// ���� ����̽� �������̽�
	ID3D11Device*					m_p3dDevice = nullptr;
	// ���� ����̽� ���� ���� �������̽�
	ID3D11DeviceContext*			m_pImmediateContext = nullptr;		
	// swapChain ����� ���ػ���
	IDXGIFactory*					m_pGIFactory = nullptr;	
	// ���� ����ü��
	IDXGISwapChain*					m_pSwapChain = nullptr;
	// ���� ���۸� ���� ������ ��
	ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;
	// ����۸� ���� ����Ÿ�ٺ並 �����Ѵ�.
	ComPtr<ID3D11RenderTargetView>	m_pRTV = nullptr;
	// �� ��Ʈ
	D3D11_VIEWPORT m_vp;

private:
	// 1) ����̽� ����
	HRESULT CreateDevice();
	// 2) ���丮 ���� (DXGI �� �ϴ� ����, ��� )
	HRESULT CreateDXGIDevice();
	// 3) ���� ü�� ����
	HRESULT CreateSwapChain();
	// 4) ����Ÿ�ٺ� ����
	HRESULT CreateRenderTargetView();
	// 4) ���� ���� ����
	HRESULT CreateDepthStencilView();
	// 5) ����Ʈ ����
	void CreateViewPort();
	// ����̽� ũ�� ������
	virtual HRESULT ResizeDevice(UINT width, UINT height) override;

	virtual HRESULT DeleteDXResource();
	virtual HRESULT CreateDXResource();
public:
	bool		PreRender();
	bool        PostRender();
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
//	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����

};
//#define I_Device DxDevice::GetInstance()
