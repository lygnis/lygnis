#pragma once
#include <iostream>
using namespace std;
class Tpoint
{
private:
	int x, y;
public:
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show(void);


public:
	Tpoint();			// ������ ȣ��
	~Tpoint();			// ������ ����
};

