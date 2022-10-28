#pragma once
#include "MActor.h"
class MyShapeLine : public MActor
{
public:
	virtual bool CreateVertexData() override;
	virtual bool CreateIndexData() override;
	virtual bool Frame();
	virtual bool Render();
public:
	MyShapeLine() {};
	virtual~MyShapeLine() {};
};
class ShapeDirectLine : public MyShapeLine
{
public:
	virtual bool CreateVertexData() override;
	virtual bool CreateIndexData() override;
public:
	ShapeDirectLine() {};
	~ShapeDirectLine() {};
};