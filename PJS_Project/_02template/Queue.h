#pragma once
#include <iostream>

template<class T>
class Queue
{
public:
	int size;
	T* data;
	int front;
	int rear;
	int count;
public:
	bool Push(T value);
	bool Pop(T& value);
public:
	Queue(int size = 10);
	~Queue();
};

template<class T>
inline bool Queue<T>::Push(T value)
{
	if (count >= size)
		return false;
	front = front + 1 % size;
	count++;
	data[front] = value;
	return true;

}

template<class T>
inline bool Queue<T>::Pop(T& value)
{
	if (count <= 0)
		return false;
	rear = (rear + 1) % rear;
	count--;
	value = data[rear];
	return true;
	
}

template<class T>
inline Queue<T>::Queue(int size)
{
	count = 0;
	this->size = size;
	data = new T[size]
	front = -1;
	rear = -1;
}

template<class T>
inline Queue<T>::~Queue()
{
	delete[] data;
}
