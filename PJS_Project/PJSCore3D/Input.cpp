#include "Input.h"
bool		Input::Init()
{
    ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
    ::GetCursorPos(&m_pMpos); // 화면좌표
    ::ScreenToClient(g_hWnd, &m_pMpos); // 클라이언트
    m_pPrevMpos = m_pMpos;
    return true;
}
DWORD  Input::GetKey(DWORD dwKey)
{
    return m_dwKeyState[dwKey];
}
bool		Input::Frame()
{
    ::GetCursorPos(&m_pMpos); // 화면좌표
    ::ScreenToClient(g_hWnd, &m_pMpos); // 클라이언트
    m_pOffset.x = m_pMpos.x - m_pPrevMpos.x;
    m_pOffset.y = m_pMpos.y - m_pPrevMpos.y;
    for (int iKey = 0; iKey < 256; iKey++)
    {
        SHORT sKey = ::GetAsyncKeyState(iKey); // 비동기 키 상태 
        if (sKey & 0x8000) // 1000 0000 0000 0000
        {
            if (m_dwKeyState[iKey] == KEY_FREE || m_dwKeyState[iKey] == KEY_UP)
                m_dwKeyState[iKey] = KEY_PUSH;
            else
                m_dwKeyState[iKey] = KEY_HOLD;
        }
        else
        {
            if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
                m_dwKeyState[iKey] = KEY_UP;
            else
                m_dwKeyState[iKey] = KEY_FREE;
        }
    }
    m_pPrevMpos = m_pMpos;
    return true;
}
bool		Input::Render()
{
    return true;
}
bool		Input::Release()
{
    return true;
}