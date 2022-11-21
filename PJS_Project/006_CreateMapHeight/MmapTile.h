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
	// 각 칸의 거리 값이 커지면 타일의 크기도 증가
	float m_fCellDistance = 5.0f;
	float m_fScaleHeight = 200.0f;
public:
	std::vector<float> m_fHeightList;
public:
	bool SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pContext);
	bool CreateMap(UINT col, UINT row);
	bool CreateVertexData()override;
	bool CreateIndexData()override;
	bool CreateHeightMap(const TCHAR* _texName);
	float GetHeightOfVertex(UINT Index);
	float GetHeight(float posX, float posZ);
	float GetHeightMap(int row, int col);
	float Lerp(float start, float end, float fTangent);
	void GetnVertexNormal();
	TVector3 ComputeFaceNormal(UINT i0, UINT i1, UINT i2);
};

