#pragma once
#include "TWindow.h"

class DxDevice : public TWindow
{
	// 소멸할때 쓰레기 값일 수도 있으니 Nullptr로 설정
	// 인터페이스 -> 하드웨어 직접 제어 -> 획득
public:
	// 생성 디바이스 인터페이스
	ID3D11Device* m_p3dDevice = nullptr;
	// 생성 디바이스 관리 제어 인터페이스
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		
	// swapChain 사용을 위해생성
	IDXGIFactory* m_pGIFactory = nullptr;	
	// 버퍼 스왑체인
	IDXGISwapChain* m_pSwapChain = nullptr;
	// 백버퍼를 통해 랜더타겟뷰를 생성한다.
	ComPtr<ID3D11RenderTargetView>	m_pRTV = nullptr;

private:
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
	// 디바이스 크기 재조정
	virtual HRESULT ResizeDevice(UINT width, UINT height) override;

	virtual HRESULT DeleteDXResource();
	virtual HRESULT CreateDXResource();
public:
	bool		PreRender();
	bool        PostRender();
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
//	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제

};
//#define I_Device DxDevice::GetInstance()
