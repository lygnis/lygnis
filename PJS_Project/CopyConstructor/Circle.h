#pragma once
#include <iostream>

using namespace std;
class Circle
{
private:
	int radius;
	int age;
public:
	Circle(const Circle& c) : radius(c.radius)	// ��������� ����
	{

	};
	Circle() : radius(1)
	{

	};
	Circle(int radius)
	{
		this->radius = radius;
	}
	double getArea()
	{
		return 3.14 * radius * radius;
	}
	int CompareAge(Circle& a, Circle& b);
};

