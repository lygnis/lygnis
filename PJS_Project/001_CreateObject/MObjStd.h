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
		t = _t
	}
};