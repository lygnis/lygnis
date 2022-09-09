#pragma once
#include<iostream>
using namespace std;
// const char& operator []() cont{}
// char& operator []()  두 함수는 별개의 함수가 된다.

// 연산자 재정의 불가
// 1. 선택 연산자 : .
// 2. 포인터 선택 연산자: *
// 3. 영역 선택 연산자: ::
// 4. 조건 연산자: ?, :
// 5. 크기 연산자: sizeof
class TRegion
{
public:
	int x, y;

public:
	// 연산자 operator
	TRegion operator++(int);
	TRegion operator++(void);
	TRegion operator+(TRegion& _i);
	TRegion operator-(const TRegion &pt) const;

	friend TRegion operator+(int pl, TRegion& pt);
	TRegion& operator=(const TRegion& pt);




public:
	TRegion(void);
	TRegion(int x, int y);
	~TRegion();
};

