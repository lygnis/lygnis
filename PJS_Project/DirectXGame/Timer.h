#pragma once
#include "MStd.h"
#pragma comment(lib, "winmm.lib")
class Timer 
{
public:

public:
	float		 m_fDeltaTime;				// 시간 변위
	float		 m_fGameTime;				// 플레이 타임
	UINT		 m_iFPS;					//FPS
	std::wstring m_szTimeNFps;		// 출력창 출력
private:
	DWORD		 m_fElapseTime;			// 현재시간
	DWORD		 m_fBeforTime;				// 이전시간
	float		 m_fFpsTime;				// FPS 시간 
	UINT		 m_iFPScount;				// FPS카운터
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	static Timer* get();
};


