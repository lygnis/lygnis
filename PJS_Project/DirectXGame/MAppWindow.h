#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
//#include "MVertexBuffer.h"

class MVertexBuffer;
class MSwapChain;

class MAppWindow :public MWindow
{
public:
	MAppWindow() {}
	~MAppWindow() {}
public:
	// MWindow을(를) 통해 상속됨
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
private:
	std::shared_ptr<MSwapChain> _swapChain;
	std::shared_ptr<MVertexBuffer> _vb;
};

