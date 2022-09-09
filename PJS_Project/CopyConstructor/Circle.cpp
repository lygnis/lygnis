#include "Circle.h"

//Circle::Circle(const Circle& c)
//{
//	this->radius = c.radius;
//	cout << "복사 생성자 실행 radius =" << radius<<endl;
//}


int main()
{
	Circle src(30);		// 일반 생성자 호출
	Circle dest(src);		// dest 객체의 복사생성자 호출
						// 복사 생성자를 만들지 않았을 경우 디폴트 복사 생성자 자동 생성


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
