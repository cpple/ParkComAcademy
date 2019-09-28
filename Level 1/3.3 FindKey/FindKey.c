/*
���ϸ�: FindKey.c
��  ��: ����� ã���� �ϴ� ���� �Է¹޾� �� ���� ��ġ���� ã�Ƽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.22
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*numbers), ULong *key);
void FindKey(ULong(*numbers), ULong key, ULong(*indexes), ULong *count);
void Output(ULong(*indexes), ULong count);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong key;
	ULong indexes[MAX];
	ULong count;
	//ȣ��
	Input(numbers, &key);
	FindKey(numbers, key, indexes, &count);
	Output(indexes, count);

	return 0;
}
/*
�Լ���: Input
��  ��: ����� Ű�� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����, Ű
*/
void Input(ULong(*numbers), ULong *key) {
	ULong i;
	printf("����\n");
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
	printf("Ű ");
	scanf("%d", key);
}
/*
�Լ���: FindKey
��  ��: ���� �߿� Ű�� ��ġ���� ã�Ƽ� ����Ѵ�.
��  ��: ����, Ű
��  ��: ��ġ��, ����(��뷮)
*/
void FindKey(ULong(*numbers), ULong key, ULong(*indexes), ULong *count) {
	ULong i;
	ULong j = 0;
	*count = 0;

	for (i = 0; i < MAX; i++) {
		if (numbers[i] == key) {
			indexes[j] = i;
			j++;
			(*count)++;
		}
	}
}
/*
�Լ���: Output
��  ��: ��ġ���� ����Ϳ� ����Ѵ�.
��  ��: ��ġ��, ����(��뷮)
��  ��: ����
*/
void Output(ULong(*indexes), ULong count) {
	ULong j = 0;
	printf("��ġ��\n");
	while (j < count) {
		printf("%d ", indexes[j] + 1);
		j++;
	}
	if (count == 0) {
		printf("ã���� �ϴ� ���� ����.\n");
	}
}
