#pragma once
#include "MActor.h"
class MShape : public MActor
{
public:
	MShape() {};
	virtual ~MShape() {};
};

class MBoxShape: public MShape
{
public:
	bool	CreateVertexData() override;
	bool	CreateIndexData() override;
	HRESULT CreateResource()override;
public:
	MBoxShape() {}
	virtual~MBoxShape() {}
};
