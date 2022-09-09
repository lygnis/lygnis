#pragma once
#include "TWindow.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include <d3d11.h>
#include "DxDevice.h"
struct SimpleVertex
{			// 정점의 위치
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
	//DxDevice m_dxDevice;			// 상속을 통해서도 가능하다

	ID3D11Buffer* m_pVertexBuffer;			// 버텍스 버퍼 생성
	// 만들어진 버퍼를 IA에 넘겨줘야 한다.
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
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제

};

