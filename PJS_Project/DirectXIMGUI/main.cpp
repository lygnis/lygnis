#include "MAppWindow.h"
#include "InputSystem.h"

int main()
{
	try
	{
		MGraphicsEngine::Create();
		InputSystem::Create();
	}
	catch (...)
	{
		return -1;
	}

	{

			
		MAppWindow app;
		while (app.IsRun())
		{
		}

		InputSystem::Release();
		MGraphicsEngine::Release();

		return -1;

	}
	InputSystem::Release();
	MGraphicsEngine::Release();

	return 0;
}