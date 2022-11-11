#pragma once
#include "MActor.h"
class MmapTile : public MActor
{
public:
	UINT m_iNumRow;
	UINT m_iNumCol;
	UINT m_iCellRows;
	UINT m_iCellCols;
	UINT m_iNumVertices;
	UINT m_iNumFace;
public:
	std::vector<float> m_fHeightList;
public:
	bool CreateMap(UINT col, UINT row);
	bool CreateVertexData()override;
	bool CreateIndexData()override;
	bool CreateHeightMap(const TCHAR* _texName);
};

