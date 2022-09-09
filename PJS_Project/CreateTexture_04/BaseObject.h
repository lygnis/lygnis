#pragma once
#include "TStd.h"
#include "Vector.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Texture.h"

struct SimpleVertex
{			// 정점의 위치
	Vector3D p;
	Vector4D c;
	Vector2D t;
};
class BaseObject
{
public:
	ID3D11Device*				m_p3dDevice = nullptr;		// 1번 디바이스 획득 (디바이스 객체)		// 소멸할때 쓰레기 값일 수도 있으니 Nullptr로 설정
	ID3D11DeviceContext*		m_pImmediateContext = nullptr;		// 즉시
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
public:
	ID3D11Buffer*				m_pVertexBuffer;			// 버텍스 버퍼 생성
	// 만들어진 버퍼를 IA에 넘겨줘야 한다.
	ID3D11InputLayout*			m_pVertexLayout;

	std::vector<SimpleVertex>	m_pVertexList;			// 버텍스 버퍼 리스트

public:
	Shader*						m_pShader;				// 쉐이더
	ShaderManager				m_shManger;				// 쉐이더 매니저
	Texture*					m_pTexture;				// 텍스쳐
	TextureManager				m_txManager;			// 텍스쳐 매니저
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateShader(std::wstring _shName);
	HRESULT LoadTexture(std::wstring _fileName);
public:
	virtual bool		Create(ID3D11Device* p3dDevice, ID3D11DeviceContext* _pImmediateContext, const wchar_t* _texName, 
								const wchar_t* _shName);
public:
	virtual bool		Init(); // 초기화
	virtual bool		Frame();// 실시간 계산
	virtual bool		Render();// 실시간 랜더링
	virtual bool		Release();// 소멸 및 삭제
public:
	BaseObject() {};
	~BaseObject() {};
};

