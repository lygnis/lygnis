#pragma once
#include "TStd.h"
#include "MObjStd.h"

class MActor
{
public:
	TVector3 m_vCenter;
	TVector3 m_vLook;
	TVector3 m_vUp;
	TVector3 m_vRight;
	bool m_bUpdateCollision;
public:
	ID3D11Device*				m_pd3dDevice;
	ID3D11DeviceContext*		m_pImmediateContext;
	DX::MDxHelper				m_dxObj;

	VS_CONSTANT_BUFFER			m_cbDatas;
	TMatrix						m_matWorld;
	TMatrix						m_matView;
	TMatrix						m_matProj;

	std::vector<DWORD>			m_IndexList;
	std::vector<PNCT_VERTEX>	m_VertexList;
public:
	virtual bool Create(ID3D11Device* pDevice, const TCHAR* pLoadShaderFile, const TCHAR* pLoadTextureString = 0);
	virtual HRESULT LoadShaderFile(ID3D11Device* _pDevice, const TCHAR* _pShaderFile);
	virtual HRESULT SetInputLayout();
	virtual bool CreateVertexData();
	virtual bool CreateIndexData();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile);
	virtual bool UpdateBuffer();
	virtual HRESULT CreateResource();
	virtual void UpdateConstantBuffer(ID3D11DeviceContext* pContext, MActor* pParentTActor = NULL);

	virtual void SetMatrix(TMatrix* pWorld, TMatrix* pView, TMatrix* pProj);
	// 바운딩 박스 및 스피어를 계산해둔다.
	virtual void SetCollisionData(TMatrix& matWorld);
	virtual bool PreRender(ID3D11DeviceContext* _pContext);
	virtual bool PostRender(ID3D11DeviceContext* _pContext);
	virtual bool Render(ID3D11DeviceContext* _pContext);
};