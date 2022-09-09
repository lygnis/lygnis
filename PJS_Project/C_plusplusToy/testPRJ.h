#pragma once
class testPRJ
{
public:
	testPRJ(void);
	testPRJ(int size);
	~testPRJ(void);
	bool SetData(int pos, int data);
	bool GetData(int pos, int data);

private:
	int* pData;
	int maxsize;
};

testPRJ::testPRJ()
{
	maxsize = 100;
	pData = new int[maxsize];
}
testPRJ::testPRJ(int size)
{
	maxsize = size;
	pData = new int[maxsize];
	
}
testPRJ::~testPRJ()
{
	delete[]pData;
}
bool testPRJ::SetData(int pos, int data)
{
	if (0 || pos >= maxsize)
	{
		return false;
	}
	pData[pos] = data;
	return true;
}

bool testPRJ::GetData(int pos, int data)
{
	if (pos < 0 || pos >= maxsize)
	{
		return false;
	}
	data = pData[pos];
	return true;
}
