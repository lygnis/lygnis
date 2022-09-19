#pragma once
#include "TStd.h"
#include "Vector.h"
#include "Timer.h"
#include "Input.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h" 
#pragma comment(lib, "DirectXTK.lib")
struct ObjectVertex
{
	Vector3D position;
	Vector4D color;
	Vector2D texture;
};

class BObject
{
public:
	// ����̽� ����
	ID3D11Device*				m_p3dDevice = nullptr;
	ID3D11DeviceContext*		m_pImmediateContext = nullptr;
	// ���ؽ� ���� ����
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pIndexBuffer;
	ID3D11InputLayout*			m_pVertexLayout;
	// ���̴� ����
	ID3D11VertexShader*			m_pVS;
	ID3D11PixelShader*			m_pPS;
	ID3DBlob*					m_pVScode;
	ID3DBlob*					m_pPScode;
	// �ؽ��� ����
	ID3D11Texture2D*			m_pTexture = nullptr;
	ID3D11ShaderResourceView*	m_pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC		m_Desc;
	std::vector<ObjectVertex>	m_pVertexList;
	std::vector<DWORD>			m_pIndexList;
public:
	bool Init();
	virtual bool Frame();
	bool Render();
	bool Release();
public:
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
	bool Create(const wchar_t* _shName, const wchar_t* _texName);
public:
	virtual HRESULT CreateVertexBuffer();		// ���ؽ� ����
	virtual HRESULT CreateIndexBuffer();		// �ε��� ����
	virtual HRESULT CreateVertexLayout();
	virtual HRESULT CreateVertexShader(std::wstring _shFile);
	virtual HRESULT CreatePixelShader(std::wstring _shFile);
	virtual HRESULT LoadTexture(std::wstring name);
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();

};
