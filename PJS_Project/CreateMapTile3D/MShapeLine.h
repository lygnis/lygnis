#pragma once
#include "BObject.h"
class MyShapeLine : public BObject
{
public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
	virtual bool Frame() override;
	virtual bool Render() override;
public:
	MyShapeLine() {};
	virtual~MyShapeLine() {};
};
class ShapeDirectLine : public MyShapeLine
{
public:
	virtual void CreateVertexData() override;
	virtual void CreateIndexData() override;
public:
	ShapeDirectLine() {};
	~ShapeDirectLine() {};
};