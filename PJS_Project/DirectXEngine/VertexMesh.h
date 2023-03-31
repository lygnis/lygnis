#pragma once
#include "TMath.h"
//using namespace TBASIS_EX;
class VertexMesh
{
public:
	VertexMesh() : _position(), _texcoord(), _normal()
	{

	}
	VertexMesh(const TVector3& position, const TVector2& texcoord, const TVector3& normal,
		const TVector3& tangent, const TVector3& binormal)
		: _position(position), _texcoord(texcoord), _normal(normal), tangent_(tangent), binormal_(binormal)
	{

	}
	VertexMesh(const VertexMesh& vertex) 
		: _position(vertex._position), _texcoord(vertex._texcoord), _normal(vertex._normal),
		tangent_(vertex.tangent_), binormal_(vertex.binormal_)
	{

	}
	~VertexMesh()
	{

	}
public:
	TVector3 _position;
	TVector2 _texcoord;
	TVector4 _color;
	TVector3 _normal;
	TVector3 tangent_;
	TVector3 binormal_;
};