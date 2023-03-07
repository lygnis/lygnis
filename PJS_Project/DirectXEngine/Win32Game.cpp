#include "Game.h"
#include "MWindow.h"
#include <Windows.h>
void Game::Run()
{
	OnCreate();

	MSG msg = {};
	while (is_running_)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			if (msg.message == WM_QUIT)
			{
				is_running_ = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		OnInternalUpdate();
	}

	OnQuit();
}


