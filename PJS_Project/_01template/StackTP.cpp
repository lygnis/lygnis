#include "StackTP.h"
#include <iostream>



int main()
{
	StackTP<int> stack(10);
	int c = 0;
	stack.Push(1);
	stack.Push(2);
	stack.Push(5);
	stack.Push(1);
	stack.Push(2);
	stack.Push(4);
	while (stack.Pop(c))
	{
		std::cout << c << std::endl;
	}
	return 0;
}