#pragma once
#include "TStd.h"
class Timer
{
public:
	float m_fGameTime = 0.0f;
	float m_fElapseTimer = 10.0f;
	UINT m_iFPS = 0;
	std::wstring m_szTimer;
private:
	DWORD m_dwBeforeTime;
	UINT m_iFPSCounter = 0;
	float m_fFPSTimer = 0.0f;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

