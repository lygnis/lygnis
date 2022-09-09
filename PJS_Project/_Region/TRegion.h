#pragma once
#include<iostream>
using namespace std;
// const char& operator []() cont{}
// char& operator []()  �� �Լ��� ������ �Լ��� �ȴ�.

// ������ ������ �Ұ�
// 1. ���� ������ : .
// 2. ������ ���� ������: *
// 3. ���� ���� ������: ::
// 4. ���� ������: ?, :
// 5. ũ�� ������: sizeof
class TRegion
{
public:
	int x, y;

public:
	// ������ operator
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

