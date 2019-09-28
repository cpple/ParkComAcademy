/*
���ϸ�: GetOdd.c
��  ��: ������ �Է¹޾� �� �� Ȧ������ �հ� �ּ� Ȧ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 7
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void GetOdd(ULong(*numbers), ULong *sum, ULong *smallest);
void Output(ULong sum, ULong smallest);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong sum;
	ULong smallest;
	//ȣ��
	Input(numbers);
	GetOdd(numbers, &sum, &smallest);
	Output(sum, smallest);

	return 0;
}
/*
�Լ���: Input
��  ��: ������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����
*/
void Input(ULong(*numbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", numbers + i);
	}
}
/*
�Լ���: GetOdd
��  ��: ���� �� Ȧ������ �հ� �ּ�Ȧ���� ���Ͽ� ����Ѵ�.
��  ��: ����
��  ��: ��, �ּڰ�
*/
void GetOdd(ULong(*numbers), ULong *sum, ULong *smallest) {
	ULong i;
	ULong remainder;
	*sum = 0;
	*smallest = 0;

	for (i = 0; i < MAX; i++) {
		remainder = numbers[i] % 2;
		if (remainder == 1) {
			(*sum) += numbers[i];
			if (numbers[i] < *smallest || *smallest == 0) {
				*smallest = numbers[i];
			}
		}
	}
}
/*
�Լ���: Output
��  ��: �հ� �ּڰ��� ����Ϳ� ����Ѵ�.
��  ��: ��, �ּڰ�
��  ��: ����
*/
void Output(ULong sum, ULong smallest) {
	printf("��: %d �ּڰ�: %d\n", sum, smallest);
}
