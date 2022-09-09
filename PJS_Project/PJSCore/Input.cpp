#include "Input.h"

bool Input::Init()
{
    ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256);
    return true;
}

bool Input::Frame()
{

    ::GetCursorPos(&m_pMpos);
    ::ScreenToClient(g_hWnd, &m_pMpos);
    for (int i = 0; i < 256; i++)
    {
        SHORT sKey = ::GetAsyncKeyState(i);
        if (sKey & 0x8000)
        {
            if (m_dwKeyState[i] == KEY_FREE || m_dwKeyState[i] == KEY_UP)
                m_dwKeyState[i] = KEY_PUSH;
            else
            {
                m_dwKeyState[i] = KEY_HOLD;
            }
            if (m_dwKeyState[i] == KEY_PUSH || m_dwKeyState[i] == KEY_HOLD)
                m_dwKeyState[i] = KEY_UP;
            else
            {
                m_dwKeyState[i] = KEY_FREE;
            }
        }
    }
    return true;
}

bool Input::Render()
{
    return true;
}

bool Input::Release()
{
    return true;
}

DWORD Input::GetKey(DWORD _key)
{
    return m_dwKeyState[_key];
}
