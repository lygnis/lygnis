#pragma once
#include "MActor.h"
class MFbxObject : public MActor
{
public:
	std::wstring m_szTextureName;
	std::vector<std::vector<PNCT_VERTEX>> vbDataList;
	std::vector<W_STR> vbTexList;
	std::vector<Texture*> m_pSubTextureList;
	std::vector<ID3D11Buffer*> m_pFbxBuffer;
public:
	W_STR m_szName;
	FbxNode* m_pFbxNode;
	FbxNode* m_pFbxParentNode;
	FbxAMatrix m_FbxLocalMatrix;
	MFbxObject* m_pParent = nullptr;
public:
	MFbxObject() {};
	~MFbxObject() {};
public:

	virtual HRESULT LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile) override;
	virtual bool PostRender(ID3D11DeviceContext* _pContext)override;
	virtual bool CreateVertexData();
	virtual HRESULT CreateVertexBuffer()override;
	//virtual bool CreateIndexData();
};

