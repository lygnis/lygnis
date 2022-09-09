#include "Timer.h"
float g_fGameTimer = 0.0f;

bool Timer::Init()
{
    m_fGameTime = 0.0f;
    m_fElapseTimer = 0.0f;
    m_dwBeforeTime = timeGetTime();     //(1000�� ������ 1��)
    return true;
}

bool Timer::Frame()
{
    DWORD dwCurrTime = timeGetTime();                       // �ʱ�ȭ �ҋ� �Լ��� ���� �ð� currTime�� ����ð�
    DWORD dwElapseTime = dwCurrTime - m_dwBeforeTime;       // ����ð����� �ʱ�ȭ�� �ð�(���� �ð�)�� ���� �ð��������� �ȴ�.
    m_fElapseTimer = dwElapseTime / 1000.0f;                // ���� �ð� sec ���·� �ٲ��ش�.
    m_fGameTime += m_fElapseTimer;                          // �ð������� ������ ��� ���� �����ش�.
    {
        m_iFPSCounter++;                                    // �ѹ� ���� ������1����
        m_fFPSTimer += m_fElapseTimer;                      
        if (m_fFPSTimer >= 1.0f)
        {
            m_iFPS = m_iFPSCounter;
            m_iFPSCounter = 0;
            m_fFPSTimer = m_fFPSTimer - 1.0f;
        }
    }
    g_fGameTimer = m_fGameTime;                             // ���â�� �ð���¿� ����
    m_dwBeforeTime = dwCurrTime;                            // ���������ӿ����� �����ð��� ���� �ð����� �����Ѵ�. (���� �����ӿ��� ����ð��� ���°�)

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
