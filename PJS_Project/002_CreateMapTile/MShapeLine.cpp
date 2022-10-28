#include "MShapeLine.h"

bool MyShapeLine::CreateVertexData()
{
	m_VertexList.resize(2);
	m_VertexList[0] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 0.0f), TVector3(0.0f, 0.0f, 0.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(TVector3(0.0f, 0.0f, 1000.0f), TVector3(0.0f, 0.0f, 0.0f),	TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
	//m_pInitVertexBuffer = m_pVertexList;
	return true;
}

bool MyShapeLine::CreateIndexData()
{
	m_IndexList.resize(2);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 1;
	return true;
}

bool MyShapeLine::Frame()
{
	return true;
}

bool MyShapeLine::Render()
{
	// 라인으로 출력
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//BObject::Render();
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

bool ShapeDirectLine::CreateVertexData()
{
	m_VertexList.resize(6);
	m_VertexList[0] = PNCT_VERTEX( TVector3(0.0f, 0.0f, 0.0f), TVector3(0.0f, 0.0f, 0.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(0.0f, 0.0f) );
	m_VertexList[1] = PNCT_VERTEX( TVector3(1.0f, 0.0f, 0.0f), TVector3(1.0f, 0.0f, 0.0f), TVector4(1.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
	m_VertexList[2] = PNCT_VERTEX( TVector3(0.0f, 0.0f, 0.0f), TVector3(0.0f, 0.0f, 0.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
	m_VertexList[3] = PNCT_VERTEX( TVector3(0.0f, 1.0f, 0.0f), TVector3(0.0f, 1.0f, 0.0f), TVector4(0.0f, 1.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
	m_VertexList[4] = PNCT_VERTEX( TVector3(0.0f, 0.0f, 0.0f), TVector3(0.0f, 0.0f, 0.0f), TVector4(0.0f, 0.0f, 1.0f, 1.0f), TVector2(1.0f, 0.0f) );
	m_VertexList[5] = PNCT_VERTEX( TVector3(0.0f, 0.0f, 1.0f), TVector3(0.0f, 0.0f, 1.0f), TVector4(0.0f, 0.0f, 0.0f, 1.0f), TVector2(1.0f, 0.0f) );
	//m_pInitVertexBuffer = m_pVertexList;
	return true;
}

bool ShapeDirectLine::CreateIndexData()
{
	m_IndexList.resize(6);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; m_IndexList[iIndex++] = 1;
	m_IndexList[iIndex++] = 2; m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; m_IndexList[iIndex++] = 5;
	return true;
}
