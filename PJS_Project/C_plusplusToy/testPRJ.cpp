#include "testPRJ.h"
#include <iostream>

using namespace std;

int main(void)
{
	testPRJ data(10);
	int i = 0;
	int val = 0;
	for (int i = 0; i <= 10; i++)
	{
		if (!data.SetData(i, i))
		{
			cout << "Fail" << endl;
		}
		if (!data.GetData(i, val))
			cout << "Data Fail" << endl;
		else
			cout << "Data" << val << endl;
	}
	return 0;
}