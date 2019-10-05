#include "Stack.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	Stack stack;
	Long object;
	Long index;
	Long ret;
	Boolean isEmpty;
	
	//1. ������ �����.
	Stack_Create(&stack, 2, sizeof(Long));
	//2. 100�� �ִ�.
	object = 100;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//3. 200�� �ִ�.
	object = 200;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 50�� �ִ�.
	object = 50;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. ������.
	index = Pop(&stack);
	if (index == -1) {
		printf("������.\n");
	}
	//����ִ��� Ȯ���Ѵ�.
	isEmpty = Stack_IsEmpty(&stack);
	if (isEmpty == TRUE) {
		printf("����ִ�.\n");
	}
	else {
		printf("������� �ʴ�.\n");
	}
	//6. ����.
	Stack_Empty(&stack);
	if (stack.top == 0) {
		printf("��� ������.\n");
	}
	//����ִ��� Ȯ���Ѵ�.
	isEmpty = Stack_IsEmpty(&stack);
	if (isEmpty == TRUE) {
		printf("����ִ�.\n");
	}
	else {
		printf("������� �ʴ�.\n");
	}
	//7. 20�� �ִ�.
	object = 20;
	Push(&stack, &object, sizeof(Long));
	Top(&stack, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. ������ �����.
	Stack_Destroy(&stack);

	return 0;
}