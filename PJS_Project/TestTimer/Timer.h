#pragma once
#include "TStd.h"
#pragma comment(lib, "winmm.lib")
class Timer
{
public:
	float m_fDeltaTime;
	float m_fElapseTime;
	float m_fBeforTime;
	float m_fGameTime;

	float m_fFpsTime;
	int	  m_iFPScount;
	int	  m_iFPS;
	std::wstring m_szTimeNFps;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

