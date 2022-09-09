#pragma once
#include "TWindow.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include <d3d11.h>
#include "DxDevice.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment(lib, "DirectXTK.lib")
//#pragma comment(lib, "DirectXTK.lib")
class Sample : public DxDevice
{
public:
	//DxDevice m_dxDevice;			// 상속을 통해서도 가능하다
	ID3D11ShaderResourceView*	m_pShaderResourceView = nullptr;
	ID3D11Resource*				m_pResource = nullptr;			// 실질적인 이미지 변수
public:
	bool		Init(); // 초기화
	bool		Frame();// 실시간 계산
	bool		Render();// 실시간 랜더링
	bool		Release();// 소멸 및 삭제

};

