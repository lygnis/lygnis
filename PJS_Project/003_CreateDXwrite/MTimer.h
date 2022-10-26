#pragma once
#include "TStd.h"
class MTimer : public SingleTone<MTimer>
{
private:
	LARGE_INTEGER	m_Frequency;		// 초당 주파수
	LARGE_INTEGER	m_Start;			// 이벤트 타이머 시작 시간
	LARGE_INTEGER	m_Elapse;			// 이벤트 타이머 경과 시간
	LARGE_INTEGER	m_FPS;				// FPS 체크 타이머
	int				m_iFramePerSecond;	// 프레임 경과 시간
	int				m_iFPSElapse;		// 초당 경과된 프레임
	bool			m_bStarted;			// 이벤트 타이머 작동 여부

public:
	LARGE_INTEGER	m_Current;			// 현재시간
	LARGE_INTEGER	m_Frame;			// 이전 프레임의 시간 체크
	float			m_fDeltaTime;		// 프레임 경과 시간
	float			m_fEventTime;		// 이벤트 타이머
	std::wstring	m_szTimeNFps;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void Reset();
	void Start();
	void Stop();
	bool IsStarted() const;
public:
	MTimer();
	~MTimer();
};

#define I_Timer MTimer::GetInstance()

