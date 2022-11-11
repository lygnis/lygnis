#include "FbxLoader.h"

bool FbxLoader::Init()
{
    m_FbxManager = FbxManager::Create();
    m_pFbxImporter = FbxImporter::Create(m_FbxManager, "");
    m_pFbxScene = FbxScene::Create(m_FbxManager, "");
    return true;
}

HRESULT FbxLoader::CreateConstantBuffer(ID3D11Device* _p3dDevice)
{
    HRESULT hr;
    for (int iBone = 0; iBone < 255; iBone++)
    {
        D3DXMatrixIdentity(&m_cbDataBone.matBone[iBone]);
    }
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER) * 1;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_cbDataBone;
    hr = _p3dDevice->CreateBuffer(&bd, &sd, &m_pAnimBoneCB);
    if (FAILED(hr))
        assert(false);
    return hr;
}

bool FbxLoader::UpdateFrame(ID3D11DeviceContext* pCOntext)
{
    m_fAnimFrame = m_fAnimFrame + I_Timer.m_fDeltaTime * m_fAnimSpeed * m_AnimScene.fFrameSpeed * m_fAnimInverse;
    if (m_fAnimFrame > m_AnimScene.iEndFrame || m_fAnimFrame < m_AnimScene.iStartFrame)
    {
        m_fAnimFrame = min(m_fAnimFrame, m_AnimScene.iEndFrame);
        m_fAnimFrame = max(m_fAnimFrame, m_AnimScene.iStartFrame);
        m_fAnimInverse *= -1.0f;
    }
    std::vector<TMatrix> matCurrentAnimList;
    for (int iBone = 0; iBone < m_pObjectList.size(); iBone++)
    {
        TMatrix matAnimation = m_pObjectList[iBone]->Interplate(m_fAnimFrame, m_AnimScene);
        D3DXMatrixTranspose(&m_cbDataBone.matBone[iBone], &matAnimation);
        matCurrentAnimList.push_back(matAnimation);
    }
    pCOntext->UpdateSubresource(m_pAnimBoneCB, 0, nullptr, &m_cbDataBone, 0, 0);

    for (int iDraw = 0; iDraw < m_pDrawObjectList.size(); iDraw++)
    {
        if (m_pDrawObjectList[iDraw]->m_dxMatrixBindPseMap.size())
        {
            for (int iBone = 0; iBone < m_pObjectList.size(); iBone++)
            {

                auto iter = m_pDrawObjectList[iDraw]->m_dxMatrixBindPseMap.find(iBone);
                if (iter != m_pDrawObjectList[iDraw]->m_dxMatrixBindPseMap.end())
                {
                    TMatrix matBind = iter->second;
                    TMatrix matAnim = matBind * matCurrentAnimList[iBone];
                    D3DXMatrixTranspose(&m_cbDataBone.matBone[iBone], &matAnim);
                }
            }
            pCOntext->UpdateSubresource(m_pDrawObjectList[iDraw]->m_pSkinBoneCB, 0, nullptr, &m_cbDataBone, 0, 0);
        }
    }
    return true;
}

bool FbxLoader::Render()
{
    for (auto obj : m_pDrawObjectList)
    {
        obj->Render(m_pContext);
    }
    return true;
}

bool FbxLoader::Release()
{
    return false;
}

bool FbxLoader::Load(C_STR filename)
{
    m_pFbxImporter->Initialize(filename.c_str());
    m_pFbxImporter->Import(m_pFbxScene);
    // 단위
    FbxSystemUnit::m.ConvertScene(m_pFbxScene);
    // 기저행렬
    FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
    m_pFbxRootNode = m_pFbxScene->GetRootNode();
    PreProcess(m_pFbxRootNode);
    // 순회한 트리중 매쉬 정보로 작업을 한다.
    for (auto tObj : m_pObjectList)
    {
        if (tObj->m_pFbxParentNode != nullptr)
        {
            auto data = m_pObjectMap.find(tObj->m_pFbxParentNode);
            tObj->SetParent(data->second);
        }
        LoadAnimation(tObj);
        FbxMesh* pFbxMesh = tObj->m_pFbxNode->GetMesh();
        if (pFbxMesh)
        {
            m_pMeshList.push_back(pFbxMesh);
            ParseMesh(pFbxMesh, tObj);
        }
    }
    return true;
}

void FbxLoader::LoadAnimation(MFbxObject* pObj)
{
    FbxNode* pNode = pObj->m_pFbxNode;
    FbxAnimStack* stackAnim = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
    FbxLongLong s = 0;
    FbxLongLong n = 0;
    FbxTime::EMode TimeMode;
    if (stackAnim)
    {
        FbxString takeName = stackAnim->GetName();
        FbxTakeInfo* take = m_pFbxScene->GetTakeInfo(takeName);
        FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
        TimeMode = FbxTime::GetGlobalTimeMode();
        FbxTimeSpan localTimeSpan = take->mLocalTimeSpan;
        FbxTime start = localTimeSpan.GetStart();
        FbxTime end = localTimeSpan.GetStop();
        FbxTime Duration = localTimeSpan.GetDirection();
        s = start.GetFrameCount(TimeMode);
        n = end.GetFrameCount(TimeMode);
    }
    m_AnimScene.iStartFrame = s;
    m_AnimScene.iEndFrame = n;
    m_AnimScene.fFrameSpeed = 40.0f;
    m_AnimScene.fTickPerFrame = 160;
    m_AnimScene.TimeMode = TimeMode;
    FbxTime time;
    for (FbxLongLong t = s; t <= n; t++)
    {
        // 샘플링 방식
        // 샘플링 방식은 각 오브젝트의 애니메이션 트랙의 행렬값을 다음 자식오브젝트에 전해줘
        // 각각의 오브젝트에 곱하면서 최종적으로 나만의 애니메이션 트랙 그중 어떤 시가느이 애니메이션 행렬값을
        // 필요할때 받아와서 쓸 수 있도록 저장을 해주는것이다.

        time.SetFrame(t, TimeMode);
        MAnimTrack track;
        track.iFrame = t;
        // 그 시간에 맞는 애니메이션 행렬을 계산해서 넘겨준다. (더미오브젝트 및 헬퍼 오브젝트 계산을 하는 함수)
        FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
        track.matAnim = DxConvertMatrix(fbxMatrix);
        D3DXMatrixDecompose(&track.s, &track.r, &track.t, &track.matAnim);
        pObj->m_AnimTrack.push_back(track);
    }
}

void FbxLoader::ParseMesh(FbxMesh* pMesh, MFbxObject* pObj)
{
    pObj->m_bSkinned = ParseMeshSkinning(pMesh, pObj);
    FbxNode* pNode = pMesh->GetNode();

    FbxAMatrix geom; // 기하(로칼)행렬(초기 정점 위치를 변환할 때 사용한다.)
    FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    geom.SetT(trans);
    geom.SetR(rot);
    geom.SetS(scale);

    FbxAMatrix normalLocalMatrix = geom;
    normalLocalMatrix = normalLocalMatrix.Inverse();
    normalLocalMatrix = normalLocalMatrix.Transpose();

    //// 월드행렬
    //FbxVector4 Translation;
    //if (pNode->LclTranslation.IsValid())
    //    Translation = pNode->LclTranslation.Get();

    //FbxVector4 Rotation;
    //if (pNode->LclRotation.IsValid())
    //    Rotation = pNode->LclRotation.Get();

    //FbxVector4 Scale;
    //if (pNode->LclScaling.IsValid())
    //    Scale = pNode->LclScaling.Get();

    /*FbxAMatrix matWorldTransform(Translation, Rotation, Scale);
    FbxAMatrix normalWorldMatrix = matWorldTransform;
    normalWorldMatrix = normalWorldMatrix.Inverse();
    normalWorldMatrix = normalWorldMatrix.Transpose();*/

    // Layer 개념
    FbxLayerElementUV* VertexUVSet = nullptr;
    FbxLayerElementVertexColor* VertexColorSet = nullptr;
    FbxLayerElementNormal* VertexNormalSet = nullptr;
    FbxLayerElementMaterial* MaterialSet = nullptr;
    FbxLayer* pFbxLayer = pMesh->GetLayer(0);
    if (pFbxLayer->GetUVs() != nullptr)
    {
        VertexUVSet = pFbxLayer->GetUVs();
    }
    if (pFbxLayer->GetUVs() != nullptr)
    {
        VertexColorSet = pFbxLayer->GetVertexColors();
    }
    if (pFbxLayer->GetNormals() != nullptr)
    {
        VertexNormalSet = pFbxLayer->GetNormals();
    }
    if (pFbxLayer->GetMaterials() != nullptr)
    {
        MaterialSet = pFbxLayer->GetMaterials();
    }
    std::string szFileName;
    int iNumMtrl = pNode->GetMaterialCount();
    std::vector<C_STR> texList;
    texList.resize(iNumMtrl);
    for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
    {
        // 24 이상의 정보가 있다.
        FbxSurfaceMaterial* pSurface = pNode->GetMaterial(iMtrl);
        if (pSurface)
        {
            auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (property.IsValid())
            {
                const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
                if (tex)
                {
					szFileName = tex->GetFileName();
					texList[iMtrl] = szFileName;
                }
            }
        }
    }
    if (iNumMtrl == 1)
    {
        pObj->m_szTextureName = GetSplitName(szFileName);
    }
    if (iNumMtrl > 1)
    {
        pObj->vbDataList.resize(iNumMtrl);
        pObj->vbDataListIW.resize(iNumMtrl);
        pObj->vbTexList.resize(iNumMtrl);
        for (int iTex = 0; iTex < iNumMtrl; iTex++)
        {
            pObj->vbTexList[iTex] = GetSplitName(texList[iTex]);
        }
    }
    int iNumPolyCount = pMesh->GetPolygonCount();
    // 3 정점 -> 1폴리곤( 삼각형)
    // 4 정점 -> 1폴리곤( 쿼드 )
    int iNumFace = 0;
    int iBasePolyIndex = 0;
    int iSubMtrl = 0;
    // 제어점
    FbxVector4* pVertexPosition = pMesh->GetControlPoints();
    for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
    {
        int iPolySize = pMesh->GetPolygonSize(iPoly);
        iNumFace = iPolySize - 2;
        if (MaterialSet)
        {
            iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
        }
        for (int iFace = 0; iFace < iNumFace; iFace++)
        {
            // 정점컬러인덱스
            int VertexColor[3] = { 0, iFace + 2, iFace + 1 };
            // 정점 인덱스
            int iCornerIndex[3];
            iCornerIndex[0] = pMesh->GetPolygonVertex(iPoly, 0);
            iCornerIndex[1] = pMesh->GetPolygonVertex(iPoly, iFace+2);
            iCornerIndex[2] = pMesh->GetPolygonVertex(iPoly, iFace+1);
            // UV 인덱스
            int iUVIndex[3];
            iUVIndex[0] = pMesh->GetTextureUVIndex(iPoly, 0);
            iUVIndex[1] = pMesh->GetTextureUVIndex(iPoly, iFace+2);
            iUVIndex[2] = pMesh->GetTextureUVIndex(iPoly, iFace+1);
            for (int iIndex = 0; iIndex < 3; iIndex++)
            {
                int vertexID = iCornerIndex[iIndex];
                FbxVector4 v2 = pVertexPosition[vertexID];
                PNCT_VERTEX tVertex;
                FbxVector4 v = geom.MultT(v2);
                //v = matWorldTransform.MultT(v);
                tVertex.p.x = v.mData[0];
                tVertex.p.y = v.mData[2];
                tVertex.p.z = v.mData[1];
                tVertex.c = TVector4(1, 1, 1, 1);
                if (VertexColorSet)
                {
                    FbxColor c = ReadColor(pMesh, VertexColorSet, iCornerIndex[iIndex], iBasePolyIndex + VertexColor[iIndex]);
                    tVertex.c.x = c.mRed;
                    tVertex.c.y = c.mGreen;
                    tVertex.c.z = c.mBlue;
                    tVertex.c.w = 1.0f;
                }
                if (VertexUVSet)
                {
                    FbxVector2 t = ReadTextureCoord(pMesh, VertexUVSet, iCornerIndex[iIndex], iUVIndex[iIndex]);
                    tVertex.t.x = t.mData[0];
                    tVertex.t.y = 1.0f - t.mData[1];
                }
                if (VertexNormalSet)
                {
                    FbxVector4 n = ReadNormal(pMesh, VertexNormalSet, iCornerIndex[iIndex], iBasePolyIndex + VertexColor[iIndex]);
                    n = normalLocalMatrix.MultT(n);
                    //n = normalWorldMatrix.MultT(n);
                    tVertex.n.x = n.mData[0];
                    tVertex.n.y = n.mData[2];
                    tVertex.n.z = n.mData[1];
                }
                IW_VERTEX IWVertex;
                if (pObj->m_bSkinned == false)
                {
                    IWVertex.i.x = m_pObjectIDMap.find(pNode)->second;
                    IWVertex.i.y = 0;
                    IWVertex.i.z = 0;
                    IWVertex.i.w = 0;
                    IWVertex.w.x = 1.0f;
                    IWVertex.w.y = 0.0f;
                    IWVertex.w.z = 0.0f;
                    IWVertex.w.w = 0.0f;
                }
                else
                {
                    MWeight* pWeight = &pObj->m_WeightList[vertexID];
                    IWVertex.i.x = pWeight->Index[0];
                    IWVertex.i.y = pWeight->Index[1];
                    IWVertex.i.z = pWeight->Index[2];
                    IWVertex.i.w = pWeight->Index[3];
                    IWVertex.w.x = pWeight->weight[0];
                    IWVertex.w.y = pWeight->weight[1];
                    IWVertex.w.z = pWeight->weight[2];
                    IWVertex.w.w = pWeight->weight[3];
                }
                if (iNumMtrl <= 1)
                {
                    pObj->m_VertexList.push_back(tVertex);
                    pObj->m_VertexList_IW.push_back(IWVertex);
                }
                else
                {
                    pObj->vbDataList[iSubMtrl].push_back(tVertex);
                    pObj->vbDataListIW[iSubMtrl].push_back(IWVertex);
                }
            }
        }
        iBasePolyIndex += iPolySize;
    }
    pObj->m_dxObj.m_iNumVertex = pObj->m_VertexList.size();
    pObj->m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
    m_pDrawObjectList.push_back(pObj);
}

void FbxLoader::PreProcess(FbxNode* pFbxNode)
{
    // 트리를 전위 순회 한다.
    // 읽은 노드중 매쉬 정보가 있는 애들만 읽어온다.
    if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
        return;

    MFbxObject* pObject = new MFbxObject;
    std::string name = pFbxNode->GetName();
    pObject->m_szName = to_mw(name);
    pObject->m_pFbxNode = pFbxNode;
    pObject->m_pFbxParentNode = pFbxNode->GetParent();
    pObject->m_iObjIndex = m_pObjectList.size();
    m_pObjectList.push_back(pObject);
    m_pObjectMap.insert(std::make_pair(pFbxNode, pObject));
    m_pObjectIDMap.insert(std::make_pair(pFbxNode, pObject->m_iObjIndex));
    int iNumChild = pFbxNode->GetChildCount();
    for (int iChild = 0; iChild < iNumChild; iChild++)
    {
        FbxNode* pChild = pFbxNode->GetChild(iChild);
        // 헬퍼오브젝트 + 지오메트리 오브젝트

        if (pChild->GetNodeAttribute()!= nullptr)
        {
            FbxNodeAttribute::EType type = pChild->GetNodeAttribute()->GetAttributeType();
            if (type == FbxNodeAttribute::eMesh || type == FbxNodeAttribute::eSkeleton || type == FbxNodeAttribute::eNull)
            {
                PreProcess(pChild);
            }
        }
    }
}

int FbxLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* MaterialSet)
{
    int iSubMtrl = 0;
    if (MaterialSet != nullptr)
    {
        switch (MaterialSet->GetMappingMode())
        {
        case FbxLayerElement::eByPolygon:
        {
            switch (MaterialSet->GetReferenceMode())
            {
            case FbxLayerElement::eIndex:
            {
                iSubMtrl = iPoly;
            }break;
            case FbxLayerElement::eIndexToDirect:
            {
                iSubMtrl = MaterialSet->GetIndexArray().GetAt(iPoly);
            }break;
            }
        }
        default:
        {
            break;
        }
        }
    }
    return iSubMtrl;
}

FbxColor FbxLoader::ReadColor(FbxMesh* pMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex)
{
    FbxColor color(1, 1, 1, 1);
    FbxLayerElement::EMappingMode mode = VertexColorSet->GetMappingMode();
    switch (mode)
    {
    case fbxsdk::FbxLayerElement::eByControlPoint:
    {
        switch (VertexColorSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        {
            color = VertexColorSet->GetDirectArray().GetAt(posIndex);
        }break;
        case FbxLayerElementUV::eIndexToDirect:
        {
            int index = VertexColorSet->GetIndexArray().GetAt(posIndex);
            color = VertexColorSet->GetDirectArray().GetAt(index);
        }break;
        }break;
    }break;
    case fbxsdk::FbxLayerElement::eByPolygonVertex:
    {
        switch (VertexColorSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        {
            color = VertexColorSet->GetDirectArray().GetAt(colorIndex);
        }break;
        case FbxLayerElementUV::eIndexToDirect:
        {
            int index = VertexColorSet->GetIndexArray().GetAt(colorIndex);
            color = VertexColorSet->GetDirectArray().GetAt(index);
        }break;
        }break;
    }break;
    }
    return color;
}

FbxVector2 FbxLoader::ReadTextureCoord(FbxMesh* pMehs, FbxLayerElementUV* VertexUVSet, int posIndex, int uvIndex)
{
    FbxVector2 t;
    /*enum EMappingMode
    {
        eNone,				// 매핑이 결정되지 않았다.
        eByControlPoint,	// 제어점 및 정점에 1개의 매핑이 되어 있다.
        eByPolygonVertex,	// 각 정점이 속한 폴리곤의 매핑에 좌표가 있다.
        eByPolygon,         // 전체 폴리곤에 매핑 좌표가 있다.
        eByEdge,			// 에지에 1개의 매핑 좌표가 있다.
        eAllSame			// 전체 폴리곤에 1개의 매핑 좌표가 있다.
    };*/
    //enum EReferenceMode
    //{
    //	eDirect,   // n번째 매핑정보가 mDirectArray의 n번째 위치에 있다.
    //	eIndex,    // fbx 5.0 이하 버전에서 사용되었었다. 이상 버전에서는 eIndexToDirect로 대체되었다.
    //	eIndexToDirect
    //};
    // 텍스처 매핑 방식이 뭐냐?
    FbxLayerElement::EMappingMode mode = VertexUVSet->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElementUV::eByControlPoint:
    {
        switch (VertexUVSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        {
            t = VertexUVSet->GetDirectArray().GetAt(posIndex);
        }break;
        case FbxLayerElementUV::eIndexToDirect:
        {
            int index = VertexUVSet->GetIndexArray().GetAt(posIndex);
            t = VertexUVSet->GetDirectArray().GetAt(index);
        }break;
        }break;
    }break;
    case FbxLayerElementUV::eByPolygonVertex:
    {
        switch (VertexUVSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        case FbxLayerElementUV::eIndexToDirect:
        {
            t = VertexUVSet->GetDirectArray().GetAt(uvIndex);
        }break;
        }break;
    }break;
    }
    return t;
}

FbxVector4 FbxLoader::ReadNormal(FbxMesh* pMehs, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex)
{
    FbxVector4 normal(1, 1, 1, 1);
    FbxLayerElement::EMappingMode mode = VertexNormalSet->GetMappingMode();
    switch (mode)
    {
    case FbxLayerElementUV::eByControlPoint:
    {
        switch (VertexNormalSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        {
            normal = VertexNormalSet->GetDirectArray().GetAt(posIndex);
        }break;
        case FbxLayerElementUV::eIndexToDirect:
        {
            int index = VertexNormalSet->GetIndexArray().GetAt(posIndex);
            normal = VertexNormalSet->GetDirectArray().GetAt(index);
        }break;
        }break;
    }break;
    case FbxLayerElementUV::eByPolygonVertex:
    {
        switch (VertexNormalSet->GetReferenceMode())
        {
        case FbxLayerElementUV::eDirect:
        case FbxLayerElementUV::eIndexToDirect:
        {
            normal = VertexNormalSet->GetDirectArray().GetAt(colorIndex);
        }break;
        }break;
    }break;
    }
    return normal;
}

TMatrix FbxLoader::DxConvertMatrix(FbxAMatrix& fbxMatrix)
{
    TMatrix m= ConvertMatrix(fbxMatrix);
    TMatrix mat;
    mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
    mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
    mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
    mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
    mat._14 = mat._24 = mat._34 = 0.0f;
    mat._44 = 1.0f;
    return mat;
}

TMatrix FbxLoader::ConvertMatrix(FbxAMatrix& fbxMatrix)
{
    TMatrix mat;
    float* tArray = (float*)(&mat);
    double* fbxArray = (double*)(&fbxMatrix);
    for (int i = 0; i < 16; i++)
    {
        tArray[i] = fbxArray[i];
    }
    return mat;
}

W_STR FbxLoader::GetSplitName(std::string szFileName)
{
    W_STR szUnicode = to_mw(szFileName);
    W_STR name;
    TCHAR drive[260] = { 0, };
    TCHAR dir[260] = { 0, };
    TCHAR filename[260] = { 0, };
    TCHAR ext[260] = { 0, };
    _tsplitpath_s(szUnicode.c_str(), drive, dir, filename, ext);
    name = filename;
    name += ext;

    return name;
}

bool FbxLoader::ParseMeshSkinning(FbxMesh* pFbxMesh, MFbxObject* pObj)
{
    // 리깅도구 (뼈대에 스킨을 붙이는 작업도구)
    int iDeformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
    if (iDeformerCount == 0) 
        return false;

    // iNumVertex == 메쉬의 정점 개수와 동일해야한다.
    int iNumVertex = pFbxMesh->GetControlPointsCount();
    pObj->m_WeightList.resize(iNumVertex);
    for (int iDeformer = 0; iDeformer < iDeformerCount; iDeformer++)
    {
        FbxDeformer* deformer = pFbxMesh->GetDeformer(iDeformer, FbxDeformer::eSkin);
        FbxSkin* pSkin = (FbxSkin*)deformer;
        int iNumClusterCount = pSkin->GetClusterCount();
        for (int iCluster = 0; iCluster < iNumClusterCount; iCluster++)
        {
            FbxCluster* pCluster = pSkin->GetCluster(iCluster);
            FbxNode* pFbxNode = pCluster->GetLink();
            if (m_pObjectIDMap.find(pFbxNode) == m_pObjectIDMap.end())
                continue;
            int iBoneIndex = m_pObjectIDMap.find(pFbxNode)->second;

            // 뼈대 공간으로 변환하는 행렬이 필요하다.
            FbxAMatrix matXBindPose;
            FbxAMatrix matReferenceGlobalInitPosition;
            pCluster->GetTransformLinkMatrix(matXBindPose);
            pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
            FbxAMatrix matBindPos = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

            TMatrix matInvBindPos = DxConvertMatrix(matBindPos);
            matInvBindPos = matInvBindPos.Invert();
            pObj->m_dxMatrixBindPseMap.insert(std::make_pair(iBoneIndex, matInvBindPos));
            // 임의의 1개 정점에 영향을 미치는 뼈대의 개수
            int iNumWeightCounter = pCluster->GetControlPointIndicesCount();
            int* pIndicss = pCluster->GetControlPointIndices();
            double* pWeights = pCluster->GetControlPointWeights();
            for (int iVertex = 0; iVertex < iNumWeightCounter; iVertex++)
            {
                int iVertexIndex = pIndicss[iVertex];
                float fWeight = pWeights[iVertex];
                pObj->m_WeightList[iVertexIndex].insert(iBoneIndex, fWeight);
            }
        }
    }
    return true;
}
