#include "FbxLoader.h"

bool FbxLoader::Init()
{
    m_FbxManager = FbxManager::Create();
    m_pFbxImporter = FbxImporter::Create(m_FbxManager, "");
    m_pFbxScene = FbxScene::Create(m_FbxManager, "");
    return true;
}

bool FbxLoader::Frame()
{
    return false;
}

bool FbxLoader::Render()
{
    return false;
}

bool FbxLoader::Release()
{
    return false;
}

bool FbxLoader::Load(C_STR filename)
{
    m_pFbxImporter->Initialize(filename.c_str());
    m_pFbxImporter->Import(m_pFbxScene);
    // ����
    FbxSystemUnit::m.ConvertScene(m_pFbxScene);
    // �������
    FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
    m_pFbxRootNode = m_pFbxScene->GetRootNode();
    PreProcess(m_pFbxRootNode);
    // ��ȸ�� Ʈ���� �Ž� ������ �۾��� �Ѵ�.
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
    pObj->m_AnimScene.iStartFrame = s;
    pObj->m_AnimScene.iEndFrame = n;
    pObj->m_AnimScene.fFrameSpeed = 40.0f;
    pObj->m_AnimScene.fTickPerFrame = 60000;
    FbxTime time;
    for (FbxLongLong t = s; t <= n; t++)
    {
        // ���ø� ���
        // ���ø� ����� �� ������Ʈ�� �ִϸ��̼� Ʈ���� ��İ��� ���� �ڽĿ�����Ʈ�� ������
        // ������ ������Ʈ�� ���ϸ鼭 ���������� ������ �ִϸ��̼� Ʈ�� ���� � �ð����� �ִϸ��̼� ��İ���
        // �ʿ��Ҷ� �޾ƿͼ� �� �� �ֵ��� ������ ���ִ°��̴�.

        time.SetFrame(t, TimeMode);
        MAnimTrack track;
        track.iFrame = t;
        // �� �ð��� �´� �ִϸ��̼� ����� ����ؼ� �Ѱ��ش�. (���̿�����Ʈ �� ���� ������Ʈ ����� �ϴ� �Լ�)
        FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
        track.matAnim = DxConvertMatrix(fbxMatrix);
        D3DXMatrixDecompose(&track.s, &track.r, &track.t, &track.matAnim);
        pObj->m_AnimTrack.push_back(track);
    }
}

void FbxLoader::ParseMesh(FbxMesh* pMesh, MFbxObject* pObj)
{
    FbxNode* pNode = pMesh->GetNode();

    FbxAMatrix geom; // ����(��Į)���(�ʱ� ���� ��ġ�� ��ȯ�� �� ����Ѵ�.)
    FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    geom.SetT(trans);
    geom.SetR(rot);
    geom.SetS(scale);

    FbxAMatrix normalLocalMatrix = geom;
    normalLocalMatrix = normalLocalMatrix.Inverse();
    normalLocalMatrix = normalLocalMatrix.Transpose();

    //// �������
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

    // Layer ����
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
        // 24 �̻��� ������ �ִ�.
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
        pObj->vbTexList.resize(iNumMtrl);
        for (int iTex = 0; iTex < iNumMtrl; iTex++)
        {
            pObj->vbTexList[iTex] = GetSplitName(texList[iTex]);
        }
    }
    int iNumPolyCount = pMesh->GetPolygonCount();
    // 3 ���� -> 1������( �ﰢ��)
    // 4 ���� -> 1������( ���� )
    int iNumFace = 0;
    int iBasePolyIndex = 0;
    int iSubMtrl = 0;
    // ������
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
            // �����÷��ε���
            int VertexColor[3] = { 0, iFace + 2, iFace + 1 };
            // ���� �ε���
            int iCornerIndex[3];
            iCornerIndex[0] = pMesh->GetPolygonVertex(iPoly, 0);
            iCornerIndex[1] = pMesh->GetPolygonVertex(iPoly, iFace+2);
            iCornerIndex[2] = pMesh->GetPolygonVertex(iPoly, iFace+1);
            // UV �ε���
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
                if (iNumMtrl <= 1)
                {
                    pObj->m_VertexList.push_back(tVertex);
                }
                else
                {
                    pObj->vbDataList[iSubMtrl].push_back(tVertex);
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
    // Ʈ���� ���� ��ȸ �Ѵ�.
    // ���� ����� �Ž� ������ �ִ� �ֵ鸸 �о�´�.
    if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
        return;

    MFbxObject* pObject = new MFbxObject;
    std::string name = pFbxNode->GetName();
    pObject->m_szName = to_mw(name);
    pObject->m_pFbxNode = pFbxNode;
    pObject->m_pFbxParentNode = pFbxNode->GetParent();

    m_pObjectList.push_back(pObject);
    m_pObjectMap.insert(std::make_pair(pFbxNode, pObject));

    int iNumChild = pFbxNode->GetChildCount();
    for (int iChild = 0; iChild < iNumChild; iChild++)
    {
        FbxNode* pChild = pFbxNode->GetChild(iChild);
        // ���ۿ�����Ʈ + ������Ʈ�� ������Ʈ
        FbxNodeAttribute::EType type = pChild->GetNodeAttribute()->GetAttributeType();
        if (type == FbxNodeAttribute::eMesh || type == FbxNodeAttribute::eSkeleton || type == FbxNodeAttribute::eNull)
        {
            PreProcess(pChild);
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
        eNone,				// ������ �������� �ʾҴ�.
        eByControlPoint,	// ������ �� ������ 1���� ������ �Ǿ� �ִ�.
        eByPolygonVertex,	// �� ������ ���� �������� ���ο� ��ǥ�� �ִ�.
        eByPolygon,         // ��ü �����￡ ���� ��ǥ�� �ִ�.
        eByEdge,			// ������ 1���� ���� ��ǥ�� �ִ�.
        eAllSame			// ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
    };*/
    //enum EReferenceMode
    //{
    //	eDirect,   // n��° ���������� mDirectArray�� n��° ��ġ�� �ִ�.
    //	eIndex,    // fbx 5.0 ���� �������� ���Ǿ�����. �̻� ���������� eIndexToDirect�� ��ü�Ǿ���.
    //	eIndexToDirect
    //};
    // �ؽ�ó ���� ����� ����?
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
