#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

int Compare(void *one, void *other);
int main(int argc, char* argv[]) {
	LinkedList linkedList;
	Node *index;
	Node* (*indexes);
	Long count;
	Long object;
	Long key;
	Long ret;
	Long i;
	Node *previous;

	//1. ���� ����Ʈ�� �����Ѵ�.
	Create(&linkedList);
	//2. 100�� �� �ڿ� �߰��Ѵ�.	100`
	object = 100;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	previous = NULL;
	linkedList.current = linkedList.head;
	//3. 200�� �� �տ� �߰��Ѵ�.	200` 100
	object = 200;
	index = AppendFromHead(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. �������� �̵��Ѵ�.			200 100`
	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. 300�� 100 �տ� �����Ѵ�.	200 300` 100
	object = 300;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. ó������ �̵��Ѵ�.			200` 300 100
	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//7. 400�� 200 �ڿ� �����Ѵ�.	200 400` 300 100
	object = 400;
	index = InsertAfter(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. 300�� �����˻��ϴ�.		200 400 300` 100
	key = 300;
	index = LinearSearchUnique(&linkedList, &key, Compare);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//9. 300�� �����ϴ�.			200 400 100`
	index = Delete(&linkedList, index);
	if (index == NULL) {
		printf("���������ϴ�\n");
	}
	//10. 100�� �������� �̵��Ѵ�.	200 400` 100
	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//11. 200�� �� �ڿ� �߰��Ѵ�.	200 400 100 200`
	object = 200;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//12. 200�� �����˻��ϴ�.		200 400 100 200`
	key = 200;
	LinearSearchDuplicate(&linkedList, &key, &indexes, &count, Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&linkedList, index, &ret, sizeof(Long));
		printf("%d\n", ret);
		i++;
	}
	//13. ó�� 200���� �̵��Ѵ�.	200` 400 100 200
	index = indexes[0];
	index = Move(&linkedList, index);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//14. �� �ڸ� �����ϴ�.			200 400 100`
	index = DeleteFromTail(&linkedList);
	if (index == NULL) {
		printf("���������ϴ�\n");
	}
	
	//15. �� ���� �����ϴ�.			400` 100
	index = DeleteFromHead(&linkedList);
	if (index == NULL) {
		printf("���������ϴ�\n");
	}
	//16. �� �ڷ� �̵��Ѵ�.			400 100`
	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//17. ���� �����Ѵ�.			-
	DeleteAllItems(&linkedList);
	if (linkedList.length == 0) {
		printf("���� ���������ϴ�\n");
	}
	//18. 500�� �� �ڿ� �߰��Ѵ�.	500`
	object = 500;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//19. 100�� 500 �տ� �����Ѵ�.	100` 500
	object = 100;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//20. ���Ḯ��Ʈ�� ���ش�.		-
	Destroy(&linkedList);

	return 0;
}
int Compare(void *one, void *other) {
	Long *one_ = (Long*)one;
	Long *other_ = (Long*)other;
	int ret;

	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_ < *other_) {
		ret = -1;
	}
	return ret;
}