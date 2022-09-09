#pragma once
#include "TStd.h"
#include "Vector.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "TextureManager.h"
#include "Texture.h"

struct SimpleVertex
{			// ������ ��ġ
	Vector3D p;
	Vector4D c;
	Vector2D t;
};
class BaseObject
{
public:
	ID3D11Device*				m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)		// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	ID3D11DeviceContext*		m_pImmediateContext = nullptr;		// ���
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
public:
	ID3D11Buffer*				m_pVertexBuffer;			// ���ؽ� ���� ����
	// ������� ���۸� IA�� �Ѱ���� �Ѵ�.
	ID3D11InputLayout*			m_pVertexLayout;

	std::vector<SimpleVertex>	m_pVertexList;			// ���ؽ� ���� ����Ʈ

public:
	Shader*						m_pShader;				// ���̴�
	ShaderManager				m_shManger;				// ���̴� �Ŵ���
	Texture*					m_pTexture;				// �ؽ���
	TextureManager				m_txManager;			// �ؽ��� �Ŵ���
public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexLayout();
	HRESULT CreateShader(std::wstring _shName);
	HRESULT LoadTexture(std::wstring _fileName);
public:
	virtual bool		Create(ID3D11Device* p3dDevice, ID3D11DeviceContext* _pImmediateContext, const wchar_t* _texName, 
								const wchar_t* _shName);
public:
	virtual bool		Init(); // �ʱ�ȭ
	virtual bool		Frame();// �ǽð� ���
	virtual bool		Render();// �ǽð� ������
	virtual bool		Release();// �Ҹ� �� ����
public:
	BaseObject() {};
	~BaseObject() {};
};

