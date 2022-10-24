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
	DWORD	m_dwKeyState[256];				// Ű�Է� ��
	POINT	m_pMpos;						//���콺 ��ġ ��
	POINT   m_pPrevMpos;
	POINT   m_pOffset;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	DWORD GetKey(DWORD _key);
};

#define I_Input Input::GetInstance() 