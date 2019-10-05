#include "Queue.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Queue queue;
	QueueNode *node;
	Long object;
	Long ret;
	Boolean isEmpty;

	//1. ť�� �����.
	Queue_Create(&queue);
	//2. 100�� �ִ�.
	object = 100;
	Put(&queue, &object, sizeof(Long));
	//3. �������� Ȯ���ϴ�.
	Rear(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 200�� �ִ�.
	object = 200;
	Put(&queue, &object, sizeof(Long));
	//5. �������� Ȯ���ϴ�.
	Rear(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. ����ִ��� Ȯ���ϴ�.
	isEmpty = Queue_IsEmpty(&queue);
	if (isEmpty == TRUE) {
		printf("����ִ�.\n");
	}
	else {
		printf("������� �ʴ�\n");
	}
	//7. ����.
	Queue_Empty(&queue);
	//8. ����ִ��� Ȯ���ϴ�.
	isEmpty = Queue_IsEmpty(&queue);
	if (isEmpty == TRUE) {
		printf("����ִ�.\n");
	}
	else {
		printf("������� �ʴ�\n");
	}
	//9. 300�� �ִ�.
	object = 300;
	Put(&queue, &object, sizeof(Long));
	//10. 50�� �ִ�.
	object = 50;
	Put(&queue, &object, sizeof(Long));
	//11. ó���� ���ϴ�.
	Front(&queue, &ret, sizeof(Long));
	printf("%d\n", ret);
	//12. ����.
	node = Get(&queue);
	if (node == NULL) {
		printf("��������.\n");
	}
	//13. ť�� �����.
	Queue_Destroy(&queue);

	return 0;
}