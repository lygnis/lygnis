#pragma once
#include "MDxHelper.h"
#include "TMath.h"
using namespace TBASIS_EX;

struct PNCT_VERTEX
{
	TVector3 p;
	TVector3 n;
	TVector4 c;
	TVector2 t;
	bool operator == (const PNCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && n == Vertex.n && c == Vertex.c && t == Vertex.t)
		{
			return true;
		}
		return false;
	}
	PNCT_VERTEX() {}
	PNCT_VERTEX(TVector3 _p, TVector3 _n, TVector4 _c, TVector2 _t)
	{
		p = _p;
		n = _n;
		c = _c;
		t = _t;
	}
};

struct VS_CONSTANT_BUFFER
{
	TMatrix matWorld;
	TMatrix matView;
	TMatrix matProj;
	TVector4 Color;
};
struct VS_CONSTANT_BONE_BUFFER
{
	TMatrix matBone[255];
};
struct IW_VERTEX
{
	TVector4 i;
	TVector4 w;
	IW_VERTEX() {};
	IW_VERTEX(TVector4 vIndex, TVector4 vWeight)
	{
		i = vIndex;
		w = vWeight;
	}
};
struct M_BOX
{
	// Common
	TVector3		vCenter;
	TVector3		vPos[8];
	// AABB
	TVector3		vMax;
	TVector3		vMin;
	// OBB
	TVector3		vAxis[3];
	float			fExtent[3];
};