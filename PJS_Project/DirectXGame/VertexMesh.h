#pragma once
#include "TMath.h"
//using namespace TBASIS_EX;
class VertexMesh
{
public:
	VertexMesh() : _position(), _texcoord()
	{

	}
	VertexMesh(TBASIS_EX::TVector3 position, TBASIS_EX::TVector2 texcoord) : _position(position), _texcoord(texcoord)
	{

	}
	VertexMesh(const VertexMesh& vertex) : _position(vertex._position), _texcoord(vertex._texcoord)
	{

	}
	~VertexMesh()
	{

	}
public:
	TBASIS_EX::TVector3 _position;
	TBASIS_EX::TVector2 _texcoord;
};