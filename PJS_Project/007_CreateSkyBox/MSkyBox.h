#pragma once
#include "MShape.h"

// skyBox�� �ؽ��� 6���� �޴´�.

class MSkyBox : public MBoxShape
{
public:
	ID3D11ShaderResourceView* m_pTexSRV[6];
};

