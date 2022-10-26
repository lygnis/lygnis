#pragma once
#include "TStd.h"
#include "MObjStd.h"
class MActor
{
public:
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pImmediateContext;
	DX::MDxHelper	m_dxObj;

	std::vector<DWORD>		 m_IndexList;
	std::vector<PNCT_VERTEX> m_VertexList;
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
};