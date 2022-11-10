#pragma once

#include "FbxObject.h"

class FbxLoader
{
public:
	// fbx 시스템
	FbxManager*		m_FbxManager;	
	// fbx파일 로드
	FbxImporter*	m_pFbxImporter;
	// Fbx 씬 파일의 화면
	FbxScene*		m_pFbxScene;
	// Fbx 씬을 그래프로 저장한다.  트리구조로 저장되어 있다.
	// 저장한 노드를 순회할 루트노드
	FbxNode*		m_pFbxRootNode;
	// fbx 메쉬 저장
	std::vector<FbxMesh*>		m_pMeshList;
	// 만들어진 오브젝트 저장
	std::vector<MFbxObject*>	m_pObjectList;
	std::vector<MFbxObject*>	m_pDrawObjectList;

	std::map<FbxNode*, MFbxObject*> m_pObjectMap;

	ID3D11DeviceContext*		m_pContext;
public:
	bool Init();
	bool Frame();
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
};

