#pragma once
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include "TStd.h"
#include<d2d1.h>
#include<d2d1helper.h>
#include<dwrite.h>
class DxWrite
{
public:
	/*float					m_fDPIScaleX;
	float					m_fDPIScaleY;
	FLOAT					m_fdpiX;
	FLOAT					m_fdpiY;*/
	ID2D1Factory*			m_d2Factory;					// ���丮 ����
	ID2D1RenderTarget*		m_dRT;							// ����Ÿ�ٺ� ����
	IDWriteFactory*			m_pDWriterFactory;				// �� �ΰ��� �������̽� ��� �������ϸ� ���X
	IDWriteTextFormat*		m_TextFormat;					// �ؽ�Ʈ ��Ʈ ũ�� �� �ʱ�ȭ
	ID2D1SolidColorBrush*	m_pTextColor;					// �ؽ�Ʈ ����
	// IDWriteTextLayout*   ���̾ƿ� ���� ��Ʈ�� ũ��� �ٲܼ� ������ ������ ���ٲ۴�.

public:
	// �ʱ�ȭ
	bool			Set(IDXGISurface* _pSurface);
	bool			Init();
	// ������
	bool			Begin();
	HRESULT			DrawText(float x, float y, std::wstring pText, D2D1::ColorF Color = D2D1::ColorF(1, 0, 0, 1));
	bool			End();
	// ��ü �Ҹ�
	bool			Release();
	// ��ü ���� �� �Ҹ�
	HRESULT			CreateDeviceIndependentResource();
	void			DiscardDeviceIndependentResource();
	HRESULT			CreateDeviceResource(IDXGISurface* _pSurface);
	void			DiscardDeviceResource();
	// ȭ�� ������ ����
	void			OnResize(UINT width, UINT height, IDXGISurface* pSurface);

public:
	DxWrite();
	~DxWrite();
};

