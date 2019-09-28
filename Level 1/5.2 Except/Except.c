/*
���ϸ�: Except.c
��  ��: ������ �Է¹޾� �ߺ����� ���� ���鸸 ��� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void Except(ULong(*numbers), ULong(*excepts), ULong *length);
void Output(ULong(*excepts), ULong length);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	ULong excepts[MAX];
	ULong length;
	//ȣ��
	Input(numbers);
	Except(numbers, excepts, &length);
	Output(excepts, length);

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
�Լ���: Except
��  ��: ���� �� �ߺ����� ���� ���鸸 ��� ����Ѵ�.
��  ��: ����
��  ��: �ߺ��ȵȼ���, ����
*/
void Except(ULong(*numbers), ULong(*excepts), ULong *length) {
	ULong i;
	ULong j;
	ULong k = 0;
	ULong count;
	*length = 0;

	for (i = 0; i < MAX; i++) {
		count = 0;
		for (j = 0; j < MAX; j++) {
			if (numbers[i] == numbers[j]) {
				count++;
			}
		}
		if (count == 1) {
			excepts[k] = numbers[i];
			k++;
			(*length)++;
		}
	}
}
/*
�Լ���: Output
��  ��: �ߺ��ȵȼ����� ����Ϳ� ����Ѵ�.
��  ��: �ߺ��ȵȼ���, ����
��  ��: ����
*/
void Output(ULong(*excepts), ULong length) {
	ULong k = 0;
	while (k < length) {
		printf("%d ", excepts[k]);
		k++;
	}
}