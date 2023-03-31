#pragma once
#include "MStd.h"
#include "TMath.h"
#include "VertexMesh.h"
#include <fbxsdk.h>
#include <map>
#include "Resource.h"
#include "MVertexBuffer.h"
#include "IndexBuffer.h"
#include <Windows.h>
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
	FbxTime::EMode TimeMode;
	UINT iStartFrame;
	UINT iEndFrame;
	float fTickPerFrame;	// 160
	float fFrameSpeed;		// 30
};
struct MWeight
{
	std::vector<int> Index;
	std::vector<float>weight;
	void insert(int iBone, float fWeight)
	{
		for (int i = 0; i < Index.size(); i++)
		{
			if (fWeight > weight[i])
			{
				for (int j = Index.size() - 1; j > i; --j)
				{
					Index[j] = Index[j - 1];
					weight[j] = weight[j - 1];
				}
				Index[i] = iBone;
				weight[i] = fWeight;
				break;
			}
		}
	}
	MWeight()
	{
		Index.resize(8);
		weight.resize(8);
	}
};

struct IW_VERTEX
{
	TVector4 i;
	TVector4 w;
	IW_VERTEX() {};
	IW_VERTEX(TVector4 vIndex, TVector4 vWeight)
	{
		i = vIndex;
		w = vWeight;
	}
};
struct VS_CONSTANT_BONE_BUFFER
{
	TMatrix matBone[255];
};

class MFbxObject : public Resource
{
public:
	std::wstring m_szTextureName;
	std::vector<std::vector<VertexMesh>> vbDataList;
	std::vector<W_STR> vbTexList;
	std::vector<TexturePtr> m_pSubTextureList;
	std::vector<ID3D11Buffer*> m_pFbxBuffer;

	std::vector<MFbxObjectPtr>	m_pFbxChilds;
	std::vector<MAnimTrack>		m_AnimTrack;
	// 가중치 버퍼
	std::vector<std::vector<IW_VERTEX>>   vbDataListIW;
	std::vector<ID3D11Buffer*>			  m_pFbxBuffer_IW;
	// 단일 메쉬
	ID3D11Buffer* m_pVertexBuffer_IW;
	std::vector<IW_VERTEX>	m_VertexList_IW;

	std::vector<MWeight> m_WeightList;
	std::map<UINT, TMatrix>m_dxMatrixBindPseMap;
public:
	bool m_bSkinned;
	TMatrix m_matAnim;
	float m_fAnimFrame = 0;
	float m_fAnimInverse = 1.0f;
	float m_fAnimSpeed = 1.0f;
	MAnimScene m_AnimScene;

	UINT	 m_iObjIndex;
	W_STR m_szName;
	FbxNode* m_pFbxNode;
	FbxNode* m_pFbxParentNode;
	FbxAMatrix m_FbxLocalMatrix;
	MFbxObject* m_pParent = nullptr;
	VS_CONSTANT_BONE_BUFFER m_cbDataBone;
	ID3D11Buffer* m_pSkinBoneCB;
public:
	MFbxObject();
	~MFbxObject();
public:
	void SetParent(MFbxObject* pObj);
	HRESULT LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile);
	bool PostRender(ID3D11DeviceContext* _pContext);
	bool CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT SetInputLayout();
	bool Release();
	TMatrix Interplate(float fFrame, MAnimScene _scene);
};

