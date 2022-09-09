#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>

extern HWND g_hWnd;
extern RECT g_rtClient;

//#define GAME_RUN(s,x,y)  GAME_START  GAME_WINDOW(s,x,y)  GAME_END

template <class T> class SingleTone
{
public:
	static T& GetInstance()
	{
		static T theSingleTone;
		return theSingleTone;
	}
};