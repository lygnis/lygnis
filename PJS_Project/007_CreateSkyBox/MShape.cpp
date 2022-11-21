#include "MShape.h"

bool MBoxShape::CreateVertexData()
{
    // ¾Õ¸é
    m_VertexList.resize(24);
    m_VertexList[0] = PNCT_VERTEX( TVector3(-1.0f, 1.0f,-1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(0.9f, 0.9f, 0.9f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[1] = PNCT_VERTEX( TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(1.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[2] = PNCT_VERTEX( TVector3(1.0f, -1.0f,-1.0f), TVector3(0.0f, 0.0f, -1.0f),TVector4(0.5f, 0.5f, 0.5f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[3] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, 0.0f, -1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f));
    // µÞ¸é                      ( {
    m_VertexList[4] = PNCT_VERTEX( TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f) ,TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[5] = PNCT_VERTEX( TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[6] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[7] = PNCT_VERTEX( TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f) );
    // ¿À¸¥ÂÊ                    ( {
    m_VertexList[8] = PNCT_VERTEX( TVector3(1.0f, 1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[9] = PNCT_VERTEX( TVector3(1.0f, 1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[10] = PNCT_VERTEX( TVector3(1.0f, -1.0f, 1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[11] = PNCT_VERTEX( TVector3(1.0f, -1.0f, -1.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f) );
    // ¿ÞÂÊ           PNCT_VERTEX((
    m_VertexList[12] = PNCT_VERTEX( TVector3(-1.0f, 1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f) ,TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[13] = PNCT_VERTEX( TVector3(-1.0f, 1.0f, -1.0f), TVector3(-1.0f, 0.0f, 0.0f) ,TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[14] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, -1.0f), TVector3(-1.0f, 0.0f,0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[15] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, 1.0f), TVector3(-1.0f, 0.0f, 0.0f), TVector4(1.0f, 1.0f, 0.0f, 1.0f), TVector2(0.0f, 1.0f) );
    // À­¸é           PNCT_VERTEX((
    m_VertexList[16] = PNCT_VERTEX( TVector3(-1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f) ,TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[17] = PNCT_VERTEX( TVector3(1.0f, 1.0f, 1.0f), TVector3(0.0f, 1.0f, 0.0f) ,TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[18] = PNCT_VERTEX( TVector3(1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f) ,TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[19] = PNCT_VERTEX( TVector3(-1.0f, 1.0f, -1.0f), TVector3(0.0f, 1.0f, 0.0f) ,TVector4(1.0f, 0.5f, 1.0f, 1.0f), TVector2(0.0f, 1.0f) );
    // ¾Æ·§¸é                     (
    m_VertexList[20] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 0.0f) );
    m_VertexList[21] = PNCT_VERTEX( TVector3(1.0f, -1.0f, -1.0f), TVector3(0.0f, -1.0f, 0.0f), TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f) );
    m_VertexList[22] = PNCT_VERTEX( TVector3(1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f) ,TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(1.0f, 1.0f) );
    m_VertexList[23] = PNCT_VERTEX( TVector3(-1.0f, -1.0f, 1.0f), TVector3(0.0f, -1.0f, 0.0f) ,TVector4(0.0f, 1.0f, 1.0f, 1.0f), TVector2(0.0f, 1.0f) );

    m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);
    m_dxObj.m_iNumVertex = (UINT)m_VertexList.size();
    return true;
}

bool MBoxShape::CreateIndexData()
{
    m_IndexList.resize(36);
    int iIndex = 0;
    // »ó´Ü
      // 5    6
      // 1    2
      // ÇÏ´Ü
      // 4    7
      // 0    3  
    // ¾Õ¸é
    //   0    1
    //   3    2
    // µÞ¸é
    //  5    4
    //  6    7
    // 
    // ¾Õ¸é ÀÎµ¦½º
    m_IndexList[iIndex++] = 0;  m_IndexList[iIndex++] = 1;  m_IndexList[iIndex++] = 2;
    m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2;  m_IndexList[iIndex++] = 3;
    // µÞ¸é
    m_IndexList[iIndex++] = 4;  m_IndexList[iIndex++] = 5;  m_IndexList[iIndex++] = 6;
    m_IndexList[iIndex++] = 6;	m_IndexList[iIndex++] = 7;  m_IndexList[iIndex++] = 4;
    m_IndexList[iIndex++] = 8;  m_IndexList[iIndex++] = 9;  m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
    m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
    m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
    m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

    m_dxObj.m_iNumIndex = (UINT)m_IndexList.size();
    m_dxObj.m_iIndexSize = sizeof(DWORD);
    return true;
}

HRESULT MBoxShape::CreateResource()
{
    m_dxObj.m_iPrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    return S_OK;
}
