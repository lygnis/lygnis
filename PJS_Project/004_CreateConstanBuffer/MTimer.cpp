#include "MTimer.h"

bool MTimer::Init()
{
    QueryPerformanceCounter(&m_Frame);
    // 고해상도 타이머 지원여부 판단.
    if (m_Frame.QuadPart == 0)
    {
        return false;
    }
    m_FPS               = m_Frame;
    m_iFramePerSecond   = 0;
    m_iFPSElapse        = 0;
    m_fDeltaTime = 0.0f;
    Start();
    return true;
}

bool MTimer::Frame()
{
    // 1프레임의 시간 체크
    // 현재 시간을 찾는다.
    QueryPerformanceCounter(&m_Current);
    m_fDeltaTime = static_cast<float>(m_Current.QuadPart - m_Frame.QuadPart) / static_cast<float>(m_Frequency.QuadPart);
    // 1초당 프레임 체크
    if (((m_Current.LowPart - m_FPS.LowPart) / m_Frequency.LowPart) >= 1)
    {
        m_iFramePerSecond = m_iFPSElapse;
        m_iFPSElapse = 0;
        m_FPS = m_Current;
    }
    m_iFPSElapse++;
    m_Frame = m_Current;
    return true;
}

bool MTimer::Render()
{
    return false;
}

bool MTimer::Release()
{
    return false;
}

void MTimer::Reset()
{
    m_bStarted = false;
    m_fEventTime = 0.0f;
    memset(&m_Start, 0, sizeof(LARGE_INTEGER));
    memset(&m_Elapse, 0, sizeof(LARGE_INTEGER));
}

void MTimer::Start()
{
    m_bStarted = true;
    m_fEventTime = 0.0f;
    QueryPerformanceCounter((LARGE_INTEGER*)&m_Start);
}

void MTimer::Stop()
{
}

bool MTimer::IsStarted() const
{
    return false;
}

MTimer::MTimer()
{
    m_bStarted = false;
    m_iFramePerSecond = 0;
    m_iFPSElapse = 0.0f;
    m_fDeltaTime = 0.0f;
    m_fEventTime = 0.0f;

    // 시스템의 주파수 변동폭을 얻어 온다. 
    QueryPerformanceCounter((LARGE_INTEGER*)&m_Frequency);
}

MTimer::~MTimer()
{
}
