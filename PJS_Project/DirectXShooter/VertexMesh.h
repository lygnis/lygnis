#pragma once
#include "TMath.h"
//using namespace TBASIS_EX;
class VertexMesh
{
public:
	VertexMesh() : _position(), _texcoord(), _normal()
	{

	}
	VertexMesh(TVector3 position, TVector2 texcoord, TVector3 normal) : _position(position), _texcoord(texcoord), _normal(normal)
	{

	}
	VertexMesh(const VertexMesh& vertex) : _position(vertex._position), _texcoord(vertex._texcoord), _normal(vertex._normal)
	{

	}
	~VertexMesh()
	{

	}
public:
	TVector3 _position;
	TVector2 _texcoord;
	TVector3 _normal;
};