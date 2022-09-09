#include "main.h"

int APIENTRY wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR ipCmdLine, int nCmdShow)
{
	main g_Main;
	g_Main.SetWindow(hinstance, L"윈도우실행", 1280, 720);
	g_Main.Run();
	return 1;
}

bool main::Init()
{
	return false;
}

bool main::Frame()
{
	return false;
}

bool main::Render()
{
	return false;
}

bool main::Realese()
{
	return false;
}
