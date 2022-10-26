#include "MShapeLine.h"

void MyShapeLine::CreateVertexData()
{
	m_pVertexList.resize(2);
	m_pVertexList[0] = ObjectVertex{ Vector3D(0.0f, 0.0f, 0.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f) };
	m_pVertexList[1] = ObjectVertex{ Vector3D(0.0f, 0.0f, 1000.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pInitVertexBuffer = m_pVertexList;
}

void MyShapeLine::CreateIndexData()
{
	m_pIndexList.resize(2);
	int iIndex = 0;
	m_pIndexList[iIndex++] = 0; m_pIndexList[iIndex++] = 1;
}

bool MyShapeLine::Frame()
{
	return true;
}

bool MyShapeLine::Render()
{
	// 라인으로 출력
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	BObject::Render();
	m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

void ShapeDirectLine::CreateVertexData()
{
	m_pVertexList.resize(6);
	m_pVertexList[0] = ObjectVertex{ Vector3D(0.0f, 0.0f, 0.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f) };
	m_pVertexList[1] = ObjectVertex{ Vector3D(1.0f, 0.0f, 0.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pVertexList[2] = ObjectVertex{ Vector3D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pVertexList[3] = ObjectVertex{ Vector3D(0.0f, 1.0f, 0.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pVertexList[4] = ObjectVertex{ Vector3D(0.0f, 0.0f, 0.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pVertexList[5] = ObjectVertex{ Vector3D(0.0f, 0.0f, 1.0f), Vector4D(0.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
	m_pInitVertexBuffer = m_pVertexList;
}

void ShapeDirectLine::CreateIndexData()
{
	m_pIndexList.resize(6);
	int iIndex = 0;
	m_pIndexList[iIndex++] = 0; m_pIndexList[iIndex++] = 1;
	m_pIndexList[iIndex++] = 2; m_pIndexList[iIndex++] = 3;
	m_pIndexList[iIndex++] = 4; m_pIndexList[iIndex++] = 5;
}
