#pragma once
#include "DxDevice.h"
#include "Vector.h"
struct ObjectVertex
{
	Vector3D position;
	Vector4D color;
	Vector2D texture;
};

class BObject
{
	// 디바이스 설정
	ID3D11Device* m_p3dDevice = nullptr;
	ID3D11DeviceContext* m_pImmediateContext = nullptr;
	// 버텍스 버퍼 생성
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	// 쉐이더 생성
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
	ID3DBlob* m_pVScode;
	ID3DBlob* m_pPScode;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
	bool Create(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, const wchar_t* _shName);
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateShader();
};
