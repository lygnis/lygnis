#include "TBox.h"

using namespace std;
struct MStudent
{
	char m_iName[6];
	int m_iAge;
	int m_iKor;
	int m_iMat;
	int m_iEng;
	int m_iTotal;
	float m_iAverage;

public:
	friend std::istream& operator >>(std::iostream& is, MStudent& data)
	{
		return is;
	}
	friend std::ostream& operator <<(std::ostream& os, MStudent& data)
	{
		os << data.m_iName<<"\t";
		os << data.m_iAge << "\t";
		os << data.m_iKor << "\t";
		os << data.m_iEng << "\t";
		os << data.m_iMat << "\t";
		os << data.m_iTotal << "\t";
		os << data.m_iAverage << "\t";
		return os;
	}
};

MStudent* SampleData();
MStudent* NewData();
void PrintAll(LinkedList<MStudent>& list);
TBox<MStudent>* Find(LinkedList<MStudent>& list);
bool SaveData(LinkedList<MStudent>& list);
bool DataRead(LinkedList<MStudent>& list);

void main()
{


	srand(time(NULL));
	LinkedList<MStudent> list;
	//DataRead(list);
	//PrintAll(list);
	//list.PushBack(NewData());
	list.PushBack(SampleData());
	list.PushBack(SampleData());
	list.PushBack(SampleData());
	list.PushBack(SampleData());
	//SaveData(list);
	PrintAll(list);
	//Find(list);
	list.erase(Find(list));
	//PrintAll(list);

	list.clear();
}

MStudent* SampleData()
{
	MStudent* mData = new MStudent;
	mData->m_iName[0] = 65+rand() % 26;
	mData->m_iName[1] = 65 + rand() % 26;
	mData->m_iName[2] = 65 + rand() % 26;
	mData->m_iName[3] = 0;
	mData->m_iAge = rand() % 10;
	mData->m_iKor = rand() % 65;
	mData->m_iMat = rand() % 65;
	mData->m_iEng = rand() % 65;
	mData->m_iTotal = mData->m_iKor + mData->m_iMat + mData->m_iEng;
	mData->m_iAverage = mData->m_iTotal / 3.f;

	return mData;
}
MStudent* NewData()
{
	MStudent* newData = new MStudent;
	cout << "Input Name" << endl;
	do
	{
		cin >> newData->m_iName;

	} while (newData->m_iName == NULL);
	cout << "Input Age" << endl;
	do
	{
		cin >> newData->m_iAge;

	} while (newData->m_iAge==NULL||newData->m_iAge>=30||newData->m_iAge<0);
	cout << "Input Korea Score" << endl;
	do
	{
		cin >> newData->m_iKor;

	} while (newData->m_iKor == NULL || newData->m_iKor >=101 || newData->m_iKor < 0);
	cout << "Input English Score" << endl;
	do
	{
		cin >> newData->m_iEng;

	} while (newData->m_iEng == NULL || newData->m_iEng >= 101 || newData->m_iEng < 0);
	cout << "Input Math Score" << endl;
	do
	{
		cin >> newData->m_iMat;

	} while (newData->m_iMat == NULL || newData->m_iMat >= 101 || newData->m_iMat < 0);
	newData->m_iTotal = newData->m_iKor + newData->m_iEng + newData->m_iMat;
	newData->m_iAverage = newData->m_iTotal / 3.f;

	return newData;
}


// 모두 출력하기
void PrintAll(LinkedList<MStudent>& list)
{
	cout << "=======================================" << endl;
	cout << "======   성적 관리 프로그램      ======" << endl;
	cout << "=======================================" << endl;
	cout << "이름\t나이\t국어\t영어\t수학\t총점\t평균" << endl;

	for (TBox<MStudent>* pNode = list.m_pHead->m_pNext;
		pNode != list.m_pTail;
		pNode = pNode->m_pNext)
	{
		MStudent* iData = pNode->m_pdata;
		cout << *iData << endl;
	}
}

TBox<MStudent>* Find(LinkedList<MStudent>& list)
{
	cout << "input Name"<<endl;
	char s[4];
	cin >> s;
	for (TBox<MStudent>* pNode = list.m_pHead->m_pNext;
		pNode!= list.m_pTail;
		pNode = pNode->m_pNext)
	{
		if (!_stricmp(pNode->m_pdata->m_iName , s))
		{
			cout << *(pNode->m_pdata) << endl;
			return pNode;
		}

	}
	return nullptr;
}
bool DataRead(LinkedList<MStudent>& list)
{
	FILE* fp;
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL)
		return false;
	int iCount = 0;
	fscanf_s(fp, "%d\n", &iCount);
	for (int i =0; i<iCount; i++)
	{
		char strBuffer[sizeof(MStudent)+1];
		MStudent* pData = new MStudent;
		fgets(strBuffer, sizeof(MStudent)+1, fp);

		sscanf(strBuffer, "%s %d %d %d %d %d %f", pData->m_iName, &pData->m_iAge, &pData->m_iKor, &pData->m_iEng, 
			&pData->m_iMat, &pData->m_iTotal, &pData->m_iAverage);
			
			/*,
			&pData->m_iKor,
			&pData->m_iEng,
			&pData->m_iMat,
			&pData->m_iTotal,
			&pData->m_iAverage*/
			
		list.PushBack(pData);
	}
}

bool SaveData(LinkedList<MStudent>& list)
{
	FILE* fp; 
	fopen_s(&fp, "data.txt", "w");
	fprintf(fp, "%d\n", list.g_iCount);
	for (TBox<MStudent>* pNode = list.m_pHead->m_pNext;
		pNode != list.m_pTail;
		pNode = pNode->m_pNext)
	{
		fprintf(fp, "%s %d %d %d %d %d %lf\n",
			pNode->m_pdata->m_iName,
			pNode->m_pdata->m_iAge,
			pNode->m_pdata->m_iKor,
			pNode->m_pdata->m_iEng,
			pNode->m_pdata->m_iMat,
			pNode->m_pdata->m_iTotal,
			pNode->m_pdata->m_iAverage);
	}
	fclose(fp);
	return true;
}

// 