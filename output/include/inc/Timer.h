#pragma once
#include "TStd.h"
#pragma comment(lib, "winmm.lib")
class Timer : public SingleTone<Timer>
{
public:

public:
	float		 m_fDeltaTime;				// �ð� ����
	float		 m_fGameTime;				// �÷��� Ÿ��
	UINT		 m_iFPS;					//FPS
	std::wstring m_szTimeNFps;		// ���â ���
private:
	DWORD		 m_fElapseTime;			// ����ð�
	DWORD		 m_fBeforTime;				// �����ð�
	float		 m_fFpsTime;				// FPS �ð� 
	UINT		 m_iFPScount;				// FPSī����
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

#define I_Timer Timer::GetInstance()
