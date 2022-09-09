#include <algorithm>
#include <iostream>
#include <vector>

class TItem
{
public:
	int iValue;
public:
	TItem(int i);
	~TItem();
	
	bool operator == (const TItem& i);


};

TItem::TItem(int i) : iValue(i)
{

}

TItem::~TItem()
{
}
struct IsCmp
{

};

bool TItem::operator == (const TItem& i)
{
	return iValue == i.iValue;
}
bool compare(const TItem &a, const TItem &b)
{
	return a.iValue < b.iValue;
}

// 클래스로 STL vector 사용하기
int main()
{
	std::vector<TItem> listItem;
	for (int i = 0; i < 5; i++)
	{
		TItem item(i);
		listItem.push_back(item);
	}
	for (int i = 0; i < 5; i++)
	{
		TItem item(i+10);
		listItem.insert(listItem.begin(), item);
	}
	for (int i = 0; i < 5; i++)
	{
		TItem item(i + 20);
		listItem.insert(listItem.end(), item);
	}
	std::sort(listItem.begin(), listItem.end(), compare);

}


