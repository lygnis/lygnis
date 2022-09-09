#include "LinkedList.h"
// 링크드리스트	(힙 메모리)
// 데이터가 끊어져있다 비연속적이다. 데이터를 추가할때마다 그때그떄 공간을 만든다. (동적할당)

// 데이터 하나를 저장하는 단위 "노드" 하나의 노드 안에는 데이터도 있지만 다음 노드를 가리키는 주소 파트도 존재

int main()
{
	// 연결형 리스트

	tLinkedList list = {};

	InitList(&list);

	PushBack(&list, 100);
	PushBack(&list, 200);
	PushBack(&list, 100);

	
	ReleaseList(&list);






	return 0;
}


// 1. 가변배열 만들어 보기
// 2. 가변배열 안에 넣은 데이터 정렬
// - 버블 정렬
