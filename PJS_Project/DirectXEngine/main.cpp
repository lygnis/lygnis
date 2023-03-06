#include "Game.h"
int main()
{
	try
	{
		Game app;
		app.Run();
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}