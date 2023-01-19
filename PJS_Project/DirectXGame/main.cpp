#include "MAppWindow.h"

int main()
{
	MAppWindow app;
	
	if (app.Init())
	{
		while (app.IsRun())
		{
			app.broadcast();
		}
	}
	return 0;
}