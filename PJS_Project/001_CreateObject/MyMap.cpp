#include "MyMap.h"

bool MyMap::Build(UINT iWidth, UINT iHeight)
{
	// 전체 셀 개수 = (iWidth-1)*(iHeigth-1)
	// 전체 페이스 개수 = (iWidth-1)*(iHeigth-1)*2
	// 전체 정점 개수 = iWidth * iHeight
	m_pVertexList.resize(iWidth * iHeight);
	int iHalfWidth = iWidth / 2;
	int iHalfHeight = iHeight / 2;
	float fCellDistance = 1.0f;
	for (int iRow = 0; iRow < iHeight; iRow++)
	{
		for (int iCol = 0; iCol < iWidth; iCol++)
		{
			m_pVertexList[iRow * iWidth + iCol].position =
				//{(float)iCol, 0.0f, (float)iHeight-iRow};
			{ (float)(iCol - iHalfWidth) * fCellDistance, 0,
				(float)(iHalfHeight - iRow) * fCellDistance };
			m_pVertexList[iRow * iWidth + iCol].color =
			{ 1,1,1,1 };
			m_pVertexList[iRow * iWidth + iCol].texture =
			{ ((float)iCol / (float)(iWidth - 1)) * 100.0f,
			  ((float)iRow / (float)(iHeight - 1)) * 100.0f };
		}
	}
	m_pIndexList.resize((iWidth - 1) * (iHeight - 1) * 2 * 3.0f);
	UINT iIndex = 0;
	for (int iRow = 0; iRow < iHeight - 1; iRow++)
	{
		for (int iCol = 0; iCol < iWidth - 1; iCol++)
		{
			UINT iNextRow = iRow + 1;
			UINT iNextCol = iCol + 1;
			m_pIndexList[iIndex + 0] = iRow * iWidth + iCol;
			m_pIndexList[iIndex + 1] = m_pIndexList[iIndex + 0] + 1;
			m_pIndexList[iIndex + 2] = iNextRow * iWidth + iCol;

			m_pIndexList[iIndex + 3] = m_pIndexList[iIndex + 2];
			m_pIndexList[iIndex + 4] = m_pIndexList[iIndex + 1];
			m_pIndexList[iIndex + 5] = m_pIndexList[iIndex + 3] + 1;

			iIndex += 6;
		}
	}
	return true;
}
