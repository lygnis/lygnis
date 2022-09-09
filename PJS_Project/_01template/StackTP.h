#pragma once

template <class T>
class StackTP
{
public:
	int size;
	int top;
	T* data;
public:
	StackTP(int size =100);
	~StackTP();
	bool Push(T value);
	bool Pop(T& value);

};

template<class T>
StackTP<T>::StackTP(int size)
{
	top = -1;			// 처음 시작 지점 설정
	this->size = size;
	data = new T[size];	// 공간할당
}

template<class T>
inline StackTP<T>::~StackTP()
{
	delete []data;
}

template<class T>
inline bool StackTP<T>::Push(T value)
{
	if (top >= size)
	{
		return false;
	}
	data[++top] = value;
	return true;
}

template<class T>
inline bool StackTP<T>::Pop(T& value)
{
	if (top < 0)
		return false;
	value = data[top--];
	return true;

}
