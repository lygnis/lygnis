#include <stdio.h>
#include "STlinkedList.h"
#include<time.h>



stLinkedList list = {};



int main()
{
	srand(time(NULL));
	int a = 1;
	Init(&list);
	printf("%d 테스트 텍스트\n", 1);
	PushBack(&list, NewNode());
	PushBack(&list, NewNode());
	PushBack(&list, NewNode());

	PrintAll(&list);

	ReleaseList(&list);
	return 0;
}
	