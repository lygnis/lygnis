#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <d3dcompiler.h>
#include <d3d11.h>
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "winmm.lib")

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