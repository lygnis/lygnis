#pragma once
#include <fbxsdk.h>
#include "FbxObject.h"
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")
class FbxLoader
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
	
	std::map<FbxNode*, MFbxObject*> m_pObjectMap;

	ID3D11DeviceContext*		m_pContext;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool Load(C_STR filename);
	void ParseMesh(FbxMesh* pMesh);
	void PreProcess(FbxNode* pFbxNode);
	int GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet);
	FbxColor ReadColor(FbxMesh* pMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex);
	FbxVector2 ReadTextureCoord(FbxMesh* pMehs, FbxLayerElementUV* VertexUVSet, int posIndex, int uvIndex);
	FbxVector4 ReadNormal(FbxMesh* pMehs, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex);

	W_STR GetSplitName(std::string szFileName);
};

