#include "Timer.h"
float g_fGameTimer = 0.0f;

bool Timer::Init()
{
    m_fGameTime = 0.0f;
    m_fElapseTimer = 0.0f;
    m_dwBeforeTime = timeGetTime();     //(1000이 지나야 1초)
    return true;
}

bool Timer::Frame()
{
    DWORD dwCurrTime = timeGetTime();                       // 초기화 할떄 함수는 이전 시간 currTime은 현재시간
    DWORD dwElapseTime = dwCurrTime - m_dwBeforeTime;       // 현재시간에서 초기화때 시간(이전 시간)을 빼면 시간변위량이 된다.
    m_fElapseTimer = dwElapseTime / 1000.0f;                // 실제 시간 sec 형태로 바꿔준다.
    m_fGameTime += m_fElapseTimer;                          // 시간변위량 지난걸 계속 증가 시켜준다.
    {
        m_iFPSCounter++;                                    // 한번 돌떄 프레임1증가
        m_fFPSTimer += m_fElapseTimer;                      
        if (m_fFPSTimer >= 1.0f)
        {
            m_iFPS = m_iFPSCounter;
            m_iFPSCounter = 0;
            m_fFPSTimer = m_fFPSTimer - 1.0f;
        }
    }
    g_fGameTimer = m_fGameTime;                             // 출력창에 시간출력용 변수
    m_dwBeforeTime = dwCurrTime;                            // 다음프레임에서의 이전시간을 현재 시간으로 설정한다. (다음 프레임에서 현재시간을 빼는것)

    return true;
}

bool Timer::Render()
{
    m_szTimer = std::to_wstring(m_fGameTime);
    m_szTimer += L" ";
    m_szTimer += std::to_wstring(m_iFPS);
    m_szTimer += L"\n";
    OutputDebugString(m_szTimer.c_str());
    return true;
}

bool Timer::Release()
{
    return true;
}
