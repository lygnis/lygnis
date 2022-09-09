#pragma once
#include "TStd.h"
#include "TWindow.h"
class DxDevice : public TWindow
{
public:
	// 인터페이스 -> 하드웨어 직접 제어 -> 획득
	// DX는 I로 시작 I D3D11 Device
	ID3D11Device* m_p3dDevice = nullptr;		// 1번 디바이스 획득 (디바이스 객체)		// 소멸할때 쓰레기 값일 수도 있으니 Nullptr로 설정
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// 즉시

	IDXGIFactory* m_pGIFactory = nullptr;		// swapChain 사용을 위해생성
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;	// 백버퍼를 통해 랜더타겟뷰를 생성한다.

public:
	// 1) 디바이스 생성
	HRESULT CreateDevice();
	// 2) 팩토리 생성 (DXGI 라 하는 바탕, 배경 )
	HRESULT CreateDXGIDevice();
	// 3) 스왑 체인 생성
	HRESULT CreateSwapChain();
	// 4) 렌더타겟뷰 생성
	HRESULT CreateRenderTargetView();
	// 5) 뷰포트 설정
	void CreateViewPort();


public:

	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
private:
	bool		TPreRender();
	bool        TPostRender();
	bool		TInit()override; // 초기화
	bool		TFrame()override;// 실시간 계산
	bool		TRender()override;// 실시간 랜더링
	bool		TRelease()override;// 소멸 및 삭제

};

