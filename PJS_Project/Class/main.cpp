#include"Tpoint.h"



int main()
{
	Tpoint x1, y1;
	x1.SetPosition(10, 20);
	y1.SetPosition(50, 60);

	x1.Move(5, 5);
	y1.Move(2, 2);

	x1.Show();
	y1.Show();

	return 0;
}