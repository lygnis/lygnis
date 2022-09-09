
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
template <class T>
class TBox
{
public:
	T* m_pdata;				// Node
	TBox* m_pNext;
	TBox* m_pPrev;

public:
	TBox()
	{
		m_pNext = m_pPrev = nullptr;
	};
	~TBox() {};
};

template <class T>
class LinkedList					// LinkedList �����Ͱ� �� ���		���ø����� �μ��� �����Ѵ�.
{					
public:
	LinkedList();
	~LinkedList();
public:
	TBox<T>* m_pHead = NULL;
	TBox<T>* m_pTail = NULL;
	TBox<T>* m_pNext = NULL;
public:
	static	int	g_iCount;

public:
	TBox<T>* operator ++(void);
	TBox<T>* operator ++(int);
public:
	void PushBack(T* pData);
	void PushBack(T* pData, TBox<T> isData);
	void PushFront(T* pData);
	void PushFront(T* pData ,TBox<T> isData);

	void clear();
	int size();
	/*T	Find(T _pData);*/				
	TBox<T>* erase(TBox<T>* pData);		// ����


};
template<class T>
int LinkedList<T>::g_iCount = 0;

template<class T>
LinkedList<T>::LinkedList()
{
	m_pHead = new TBox<T>;		// �������� �������� �����Ҵ�
	m_pTail = new TBox<T>;
	m_pHead->m_pNext = m_pTail;
	m_pTail->m_pPrev = m_pHead;
	m_pHead->m_pPrev = nullptr;
	m_pTail->m_pNext = nullptr;

}

template<class T>
LinkedList<T>::~LinkedList()
{
	free(m_pHead);
	free(m_pTail);
}

template<class T>
inline TBox<T>* LinkedList<T>::operator++(void)
{
	if (this->m_pNext == nullptr)
		return nullptr;
	this = this->m_pNext;
	return this;
}

template<class T>
void LinkedList<T>::PushBack(T* pData)			// �ڷ� ����
{
	TBox<T>* pNewNode = new TBox<T>;
	pNewNode->m_pdata = pData;					// ������ data
	TBox<T>* pCurNode = m_pTail->m_pPrev;		// ���� ���
	m_pTail->m_pPrev = pNewNode;
	pNewNode->m_pPrev = pCurNode;
	pNewNode->m_pNext = m_pTail;
	
	pCurNode->m_pNext = pNewNode;
	g_iCount++;
}
template <class T>
void LinkedList<T>::PushBack(T* _pData, TBox<T> isData)
{
	TBox<T>* pNewNode = new TBox<T>;
	pNewNode->m_pdata = _pData;
	if (isData == NULL)
	{
		PushBack(_pData);
	}
	else
	{
		TBox <T>* pNode = isData->m_pNext;
		isData->m_pNext = pNewNode;
		pNewNode->m_pNext = pNode;

		pNewNode->m_pPrev = isData;
		pNode->m_pPrev = pNewNode;
	}
}

template<class T>
void LinkedList<T>::PushFront(T* pData)			// ������ ����
{
	TBox<T>* pNewNode = new TBox<T>;
	pNewNode->m_pdata = pData;
	TBox<T>* pCurNode = m_pHead->m_pNext;

	m_pHead->m_pNext = pNewNode;
	pNewNode->m_pNext = pCurNode;
	pNewNode->m_pPrev = m_pHead;
	pCurNode->m_pPrev = pNewNode;
	g_iCount++;
}

template<class T>
void LinkedList<T>::PushFront(T* pData, TBox<T> isData)
{
	TBox<T> pNewNode = new TBox<T>;
	pNewNode->m_pdata = pData;
	if (isData == NULL)
	{
		PushFront(pData);
	}
	else
	{
		TBox<T>* saNode = isData->m_pPrev;
		isData->m_pPrev = pNewNode;
		pNewNode->m_pPrev = saNode;
		saNode->m_pNext = pNewNode;
		pNewNode->m_pNext = isData;

		g_iCount++;
	}
}


template<class T>
void LinkedList<T>::clear()
{
	TBox<T>* pNode = m_pHead->m_pNext;
	while (pNode!=m_pTail)
	{
		TBox<T>* saNode = pNode->m_pNext;
		free(pNode);
		pNode = saNode;
	}
}

template<class T>
inline int LinkedList<T>::size()
{
	return g_iCount;
}

//template<class T>
//T LinkedList<T>::Find(T _pData)
//{
//	for (TBox<T>* pNode = m_pHead->m_pNext;
//		pNode != m_pHead;
//		pNode = pNode->m_pNext)
//	{
//		if (pNode->m_pdata == _pData)
//		{
//			return pNode->m_pdata;
//		}
//		return nullptr;
//	}
//}

template<class T>
TBox<T>* LinkedList<T>::erase(TBox<T>* pData)
{
	TBox<T>* pPrev = pData->m_pPrev;
	TBox<T>* pNext = pData->m_pNext;
	delete pData;
	pData = nullptr;
	pPrev->m_pNext = pNext;
	pNext->m_pPrev = pPrev;
	return pNext;
}
