#pragma once
#include "BObject.h"
class Object3D : public BObject
{
public:
	Object3D() {};
	virtual~Object3D() {};
};

class MyShape : public Object3D
{
public:
	MyShape() {};
	virtual~MyShape() {};
};

class ShapeBox : public Object3D
{
public:
	ShapeBox() {};
	virtual~ShapeBox() {};
public:
	virtual bool Frame()override;
	virtual void CreateVertexData()override;
	virtual void CreateIndexData()override;
	virtual bool Render()override;
};




