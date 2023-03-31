#pragma once

#include "FbxObject.h"

class FbxLoader : public Resource
{
public:
	// fbx �ý���
	FbxManager*		m_FbxManager;	
	// fbx���� �ε�
	FbxImporter*	m_pFbxImporter;
	// Fbx �� ������ ȭ��
	FbxScene*		m_pFbxScene;
	// Fbx ���� �׷����� �����Ѵ�.  Ʈ�������� ����Ǿ� �ִ�.
	// ������ ��带 ��ȸ�� ��Ʈ���
	FbxNode*		m_pFbxRootNode;
	// fbx �޽� ����
	std::vector<FbxMesh*>		m_pMeshList;
	// ������� ������Ʈ ����
	std::vector<MFbxObject*>	m_pObjectList;
	std::vector<MFbxObject*>	m_pDrawObjectList;

	std::map<FbxNode*, MFbxObject*> m_pObjectMap;
	// ������� �ε���
	std::map<FbxNode*, UINT>		m_pObjectIDMap;
	ID3D11DeviceContext*		m_pContext;
	VS_CONSTANT_BONE_BUFFER		m_cbDataBone;
public:
	MAnimScene m_AnimScene;
	float	m_fAnimFrame = 0;
	float	m_fAnimInverse = 1.0f;
	float	m_fAnimSpeed = 1.0f;
	ID3D11Buffer* m_pAnimBoneCB;
public:
	HRESULT CreateConstantBuffer(ID3D11Device* _p3dDevice);
	bool UpdateFrame(ID3D11DeviceContext* pCOntext);
	bool Render();
	bool Release();
	bool Load(C_STR filename);
	void LoadAnimation(MFbxObject* pObj);
	void ParseMesh(FbxMesh* pMesh, MFbxObject* pObj);
	void PreProcess(FbxNode* pFbxNode);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
	FbxColor ReadColor(FbxMesh* pMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex);
	FbxVector2 ReadTextureCoord(FbxMesh* pMehs, FbxLayerElementUV* VertexUVSet, int posIndex, int uvIndex);
	FbxVector4 ReadNormal(FbxMesh* pMehs, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex);
	TMatrix DxConvertMatrix(FbxAMatrix& fbxMatrix);
	TMatrix ConvertMatrix(FbxAMatrix& fbxMatrix);
	W_STR GetSplitName(std::string szFileName);
	bool ParseMeshSkinning(FbxMesh* pFbxMesh, MFbxObject* pObj);
public:
	FbxLoader(const wchar_t* full_path, ResourceManager* manager);
	~FbxLoader() {};
};

