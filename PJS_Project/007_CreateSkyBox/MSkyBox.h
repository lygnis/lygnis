#pragma once
#include "MShape.h"

// skyBox는 텍스쳐 6장을 받는다.

class MSkyBox : public MBoxShape
{
public:
	ID3D11ShaderResourceView* m_pTexSRV[6];
};

