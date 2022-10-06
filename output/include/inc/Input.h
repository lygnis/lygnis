#pragma once
#include "TStd.h"
enum KeyType
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};
class Input : public SingleTone<Input>
{
public:
	DWORD	m_dwKeyState[256];				// 키입력 값
	POINT	m_pMpos;						//마우스 위치 값
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	DWORD GetKey(DWORD _key);
};

#define I_Input Input::GetInstance() 