#include "Circle.h"

//Circle::Circle(const Circle& c)
//{
//	this->radius = c.radius;
//	cout << "���� ������ ���� radius =" << radius<<endl;
//}


int main()
{
	Circle src(30);		// �Ϲ� ������ ȣ��
	Circle dest(src);		// dest ��ü�� ��������� ȣ��
						// ���� �����ڸ� ������ �ʾ��� ��� ����Ʈ ���� ������ �ڵ� ����


	return 0;
}

int Circle::CompareAge(Circle& a, Circle& b)
{
	if (a.age > b.age)
		return 1;

	else
	{
		return 0;
	}
}
