#include "SpaceShooterGame.h"
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
		try
		{
			SpaceShooterGame app;
			while (app.IsRun())
			{
			}
		}
		catch (...)
		{
			InputSystem::Release();
			MGraphicsEngine::Release();

			return -1;
		}
		
	}
	InputSystem::Release();
	MGraphicsEngine::Release();
	return 0;
}