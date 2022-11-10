#pragma once
#include "MActor.h"
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")
struct MAnimTrack
{
	UINT iFrame;			// fTime
	TMatrix matAnim;		// self * parent
	TMatrix matSetlAnim;	// matAnim* inv(parent)
	TVector3 t;
	TQuaternion r;
	TVector3 s;
};
struct MAnimScene
{
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame;	// 160
	float fFrameSpeed;		// 30
};
class MFbxObject : public MActor
{
public:
	std::wstring m_szTextureName;
	std::vector<std::vector<PNCT_VERTEX>> vbDataList;
	std::vector<W_STR> vbTexList;
	std::vector<Texture*> m_pSubTextureList;
	std::vector<ID3D11Buffer*> m_pFbxBuffer;

	std::vector<MFbxObject*>	m_pFbxChilds;
	std::vector<MAnimTrack>		m_AnimTrack;

public:
	TMatrix m_matAnim;
	float m_fAnimFrame = 0;
	float m_fAnimInverse = 1.0f;
	float m_fAnimSpeed = 1.0f;
	MAnimScene m_AnimScene;

	W_STR m_szName;
	FbxNode* m_pFbxNode;
	FbxNode* m_pFbxParentNode;
	FbxAMatrix m_FbxLocalMatrix;
	MFbxObject* m_pParent = nullptr;
public:
	MFbxObject() {};
	~MFbxObject() {};
public:
	void SetParent(MFbxObject* pObj);
	virtual HRESULT LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile) override;
	virtual bool PostRender(ID3D11DeviceContext* _pContext)override;
	virtual bool CreateVertexData();
	virtual HRESULT CreateVertexBuffer()override;
	bool Release();
	TMatrix Interplate(float fFrame);
	//virtual bool CreateIndexData();
};

