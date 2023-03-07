#pragma once
#include "DX3D/Math/Rect.h"
#include "MStd.h"
#include "MWindow.h"

class Display : public MWindow
{
public:
	// ������ �ʱ�ȭ
	Display(Game* game);
	~Display();
protected:
	virtual void OnSize();
private:
	SwapChainPtr swap_chain_;
	Game* game_ = nullptr;

	friend class MGraphicsEngine;
};

