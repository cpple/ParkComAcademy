/*
�Լ���: Merge.c
��  ��: ������������ ���ĵ� �� �迭�� �Է¹޾� ������������ ������ ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.24
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*firstNumbers), ULong(*secondNumbers));
void Merge(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergedNumbers));
void Output(ULong(*mergedNumbers));

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong firstNumbers[MAX];
	ULong secondNumbers[MAX];
	ULong mergedNumbers[MAX*2];
	//ȣ��
	Input(firstNumbers, secondNumbers);
	Merge(firstNumbers, secondNumbers, mergedNumbers);
	Output(mergedNumbers);

	return 0;
}
/*
�Լ���: Input
��  ��: ù��°����, �ι�°������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ù��°����, �ι�°����
*/
void Input(ULong(*firstNumbers), ULong(*secondNumbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", firstNumbers + i);
	}
	for (i = 0; i < MAX; i++) {
		scanf("%d", secondNumbers + i);
	}
}
/*
�Լ���: Merge
��  ��: ù��°����, �ι�°������ ������������ �����Ͽ� ����Ѵ�.
��  ��: ù��°����, �ι�°����
��  ��: ���յȼ���
*/
void Merge(ULong(*firstNumbers), ULong(*secondNumbers), ULong(*mergedNumbers)) {
	ULong i = 0;
	ULong j = 0;
	ULong k = 0;

	while (i < MAX && j < MAX) {
		if (firstNumbers[i] < secondNumbers[j]) {
			mergedNumbers[k] = firstNumbers[i];
			k++;
			i++;
		}
		else {
			mergedNumbers[k] = secondNumbers[j];
			k++;
			j++;
		}
	}
	while (i < MAX) {
		mergedNumbers[k] = firstNumbers[i];
		k++;
		i++;
	}
	while (j < MAX) {
		mergedNumbers[k] = secondNumbers[j];
		k++;
		j++;
	}
}
/*
�Լ���: Output
��  ��: ���յ� ������ ����Ϳ� ����Ѵ�.
��  ��: ���յ� ����
��  ��: ����
*/
void Output(ULong(*mergedNumbers)) {
	ULong k;
	for (k = 0; k < MAX*2; k++) {
		printf("%d ", mergedNumbers[k]);
	}
}