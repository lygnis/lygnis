#include <stdio.h>
#include "STlinkedList.h"
#include<time.h>



stLinkedList list = {};



int main()
{
	srand(time(NULL));
	int a = 1;
	Init(&list);
	printf("%d �׽�Ʈ �ؽ�Ʈ\n", 1);
	PushBack(&list, NewNode());
	PushBack(&list, NewNode());
	PushBack(&list, NewNode());

	PrintAll(&list);

	ReleaseList(&list);
	return 0;
}
	