#pragma once
#include "BObject.h"
#include "MShapeLine.h"

class Object3D : public BObject
{
public:
	Vector3D m_vPos;
	Vector3D m_vLook;
	Vector3D m_vUp;
	Vector3D m_vRight;

public:
	Object3D() {};
	virtual~Object3D() {};
};

class ShapeBox : public Object3D
{
public:
	ShapeDirectLine* m_pDirLinShape;

public:
	ShapeBox() {};
	virtual~ShapeBox() {};
public:
	bool Init();
	bool Frame()override;
	bool Render()override;
	bool Release();
	virtual void CreateVertexData()override;
	virtual void CreateIndexData()override;
	virtual void SetMatrix(MyMatrix4X4* _matWorld, MyMatrix4X4* _matView, MyMatrix4X4* _matProj)override;
};




