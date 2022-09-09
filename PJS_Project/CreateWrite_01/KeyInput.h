#pragma once
#include "TStd.h"
enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};
class KeyInput : public  SingleTone<KeyInput>
{
public:
	DWORD		m_dwKeyState[256];			// 마우스버튼 + 키버튼
public:
	POINT		m_ptPos;					// 마우스 커서 포지션
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	DWORD GetKey(DWORD dwKey);
};

#define I_Input KeyInput::GetInstance()
