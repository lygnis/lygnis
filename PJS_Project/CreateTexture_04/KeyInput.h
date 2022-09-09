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
	DWORD		m_dwKeyState[256];			// ���콺��ư + Ű��ư
public:
	POINT		m_ptPos;					// ���콺 Ŀ�� ������
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	DWORD GetKey(DWORD dwKey);
};

#define I_Input KeyInput::GetInstance()
