#include "BumpMapping.h"
#include "InputSystem.h"
int main()
{
	try
	{
		MGraphicsEngine::Create();
	}
	catch (...)
	{
		return -1;
	}

	{
		try
		{
			BumpMapping app;
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