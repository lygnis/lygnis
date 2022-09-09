#include "Tpoint.h"

void Tpoint::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Tpoint::Move(int _x, int _y)
{
	x += _x;
	y += _y;
}

void Tpoint::Show(void)
{
	cout << "(" << x << "," << y << ")" << endl;
}

Tpoint::Tpoint()
{
	cout << "Start" << endl;
}

Tpoint::~Tpoint()
{
	cout << "End" << endl;
}
