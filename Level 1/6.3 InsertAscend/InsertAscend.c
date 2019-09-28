/*
���ϸ�: InsertAscend.c
��  ��: ������ ������������ �����Ͽ� ���� �� ����� ���� �� ������ �Բ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.24
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
void Input(Long(*numbers));
void Ascend(Long(*numbers), Long(*ascends));
void Output(Long(*numbers), Long(*ascends));

//���Ǻ�
int main(int argc, char* argv[]) {
	Long numbers[MAX];
	Long ascends[MAX];
	//ȣ��
	Input(numbers);
	Ascend(numbers, ascends);
	Output(numbers, ascends);

	return 0;
}
/*
�Լ���: Input
��  ��: ������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����
*/
void Input(Long(*numbers)) {
	Long i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
}
/*
�Լ���: Ascend
��  ��: ������ �������� ������ ������������ ���� ����Ѵ�.
��  ��: ����
��  ��: ����������
*/
void Ascend(Long(*numbers), Long(*ascends)) {
	Long i;
	Long j;
	Long temp;

	for (i = 0; i < MAX; i++) {
		ascends[i] = numbers[i];
	}
	for (i = 1; i < MAX; i++) {
		temp = ascends[i];
		j = i - 1;
		while (j >= 0 && temp < ascends[j]) {
			ascends[j + 1] = ascends[j];
			j--;
		}
		ascends[j + 1] = temp;
	}
}
/*
�Լ���: Output
��  ��: ����� ������������ ����Ϳ� ����Ѵ�.
��  ��: ����, ����������
��  ��: ����
*/
void Output(Long(*numbers), Long(*ascends)) {
	Long i;
	for (i = 0; i < MAX; i++) {
		printf("%d ", numbers[i]);
	}printf("\n");
	for (i = 0; i < MAX; i++) {
		printf("%d ", ascends[i]);
	}
}