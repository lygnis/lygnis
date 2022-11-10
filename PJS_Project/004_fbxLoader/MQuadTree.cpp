#include "MQuadTree.h"

bool MQuadTree::Create(ID3D11DeviceContext* pContext, DebugCamera* pMainCamera, MmapTile* pMap, int iMaxDepth)
{
    pMap->m_pImmediateContext = pContext;
    m_pImmediateContext = pContext;
    m_Camera = pMainCamera;
    m_iMaxDepth = iMaxDepth;
    m_pMap = pMap;
    m_pRootNode = new MNode(nullptr, m_pMap, 0, pMap->m_iNumRow - 1, pMap->m_iNumRow * (pMap->m_iNumCol - 1), 
        (pMap->m_iNumRow * m_pMap->m_iNumCol) - 1, pMap->m_iNumRow, pMap->m_iNumCol);
    BuildTree(m_pRootNode);
    return true;
}

void MQuadTree::BuildTree(MNode* pNode)
{
    if (pNode == nullptr)
        return;
    if (IsSubDivide(pNode) == false)
    {
        pNode->m_bLeaf = true;
        m_pLeafNodeList.push_back(pNode);
        return;
    }
    pNode->CreateChildNode(pNode, m_pMap, m_pMap->m_iNumRow, m_pMap->m_iNumCol);

    BuildTree(pNode->m_pChildNode[0]);
    BuildTree(pNode->m_pChildNode[1]);
    BuildTree(pNode->m_pChildNode[2]);
    BuildTree(pNode->m_pChildNode[3]);
}

bool MQuadTree::Frame()
{
    m_pDrawLeafNodeList.clear();
    VisibleNode(m_pRootNode);
    return false;
}

bool MQuadTree::Render()
{
    for (auto node : m_pDrawLeafNodeList)
    {
        m_pMap->PreRender(m_pImmediateContext);
        m_pMap->m_pImmediateContext->IASetIndexBuffer(node->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        m_pMap->UpdateConstantBuffer(m_pImmediateContext);
        m_pMap->m_pImmediateContext->DrawIndexed(node->m_dwFace * 3, 0, 0);
    }
    return true;
}

MNode* MQuadTree::VisibleNode(MNode* pNode)
{
    //T_POSITION dwRet = m_Camera->m_vFrustum.C
    T_POSITION dwRet = m_Camera->m_vFrustum.ClassifyBox(pNode->m_tBox);
    dwRet = P_SPANNING;
    if (P_FRONT == dwRet)
    {
        m_pDrawLeafNodeList.push_back(pNode);
        return pNode;
    }
    if (dwRet == P_SPANNING)
    {
        if (pNode->m_bLeaf)
        {
            m_pDrawLeafNodeList.push_back(pNode);
        }
        else
        {
            for (int iNode = 0; iNode < 4; iNode++)
            {
                VisibleNode(pNode->m_pChildNode[iNode]);
            }
        }
    }
    //return nullptr;
}

bool MQuadTree::IsSubDivide(MNode* pNode)
{
    if ((pNode->m_dCorner[1] - pNode->m_dCorner[0]) == 1)
        return false;
    if (pNode->m_iDepth < m_iMaxDepth)
        return true;
    return false;
}

bool MQuadTree::Release()
{
    m_pLeafNodeList.clear();
    m_pDrawLeafNodeList.clear();
    delete m_pRootNode;
    return true;
}
