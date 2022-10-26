#pragma once
#include "TStd.h"
#include "Vector.h"
#include "Timer.h"
#include "Input.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h" 
#include "MyMatrix.h"
#include "TMath.h"
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK.lib")
#else 
#pragma comment(lib, "DirectXTK_R.lib")
#endif
struct ObjectVertex
{
	Vector3D position;
	Vector4D color;
	Vector2D texture;
};
struct VS_CONSTANT_BUFFER
{
	// 월드 행렬
	MyMatrix4X4 matWorld;
	// 뷰 행렬
	MyMatrix4X4 matView;
	// 투영 행렬
	MyMatrix4X4 matProj;
};

class BObject
{
public:
	bool m_bInsNullable = true;
	MyMatrix4X4 m_matWorld;
	MyMatrix4X4 m_matView;
	MyMatrix4X4 m_matProj;
public:
	// 디바이스 설정
	ID3D11Device*				m_p3dDevice = nullptr;
	ID3D11DeviceContext*		m_pImmediateContext = nullptr;
	// 버텍스 버퍼 생성
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11Buffer*				m_pConstantBuffer;
	VS_CONSTANT_BUFFER			m_cbData;
	ID3D11InputLayout*			m_pVertexLayout;
	// 쉐이더 생성
	ID3D11VertexShader*			m_pVS;
	ID3D11PixelShader*			m_pPS;
	ID3DBlob*					m_pVScode;
	ID3DBlob*					m_pPScode;
	// 텍스쳐 생성
	ID3D11Texture2D*			m_pTexture = nullptr;
	ID3D11ShaderResourceView*	m_pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_Desc;
	std::vector<ObjectVertex>	m_pVertexList;
	std::vector<ObjectVertex>	m_pInitVertexBuffer;
	std::vector<DWORD>			m_pIndexList;
public:
	bool Init();
	virtual bool Frame();
	virtual bool Render();
	bool Release();
public:
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
	bool Create(const wchar_t* _shName, const wchar_t* _texName);
public:
	virtual HRESULT CreateVertexBuffer();		// 버텍스 버퍼
	virtual HRESULT CreateIndexBuffer();		// 인덱스 버퍼
	virtual HRESULT CreateConstantBuffer();		// 상수버퍼
	virtual HRESULT CreateVertexLayout();
	virtual HRESULT CreateVertexShader(std::wstring _shFile);
	virtual HRESULT CreatePixelShader(std::wstring _shFile);
	virtual HRESULT LoadTexture(std::wstring name);
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	void UpdateVertexBuffer();
	void UpdateConstantBuffer();
	void CreateConstantData();
	virtual void SetMatrix(MyMatrix4X4* _matWorld, MyMatrix4X4* _matView, MyMatrix4X4* _matProj);
};
