#pragma once
#include "TWindow.h"
#include "MTimer.h"
#include "DxWrite.h"
class Sample : public TWindow
{
public:
	DxWrite		m_Font;
	//IDXGISurface* m_pBackBuffer;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
public:
	Sample() {}
	~Sample() {}
};

