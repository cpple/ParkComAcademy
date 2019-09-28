/*
���ϸ�: DescendArray.c
��  ��: �� ������ �Է¹޾� ������������ �����Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.22
*/
#include<stdio.h>
#define MAX 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*numbers));
void DescendArray(ULong(*numbers));
void Output(ULong(*numbers));

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong numbers[MAX];
	//ȣ��
	Input(numbers);
	DescendArray(numbers);
	Output(numbers);

	return 0;
}
/*
�Լ���: Input
��  ��: �� ������ �ܺ��Է¹޴´�.
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
�Լ���: DescendArray
��  ��: ������ ������������ �����Ѵ�.
��  ��: ����
��  ��: ����
*/
void DescendArray(ULong(*numbers)) {
	ULong i;
	ULong j;
	ULong temp;

	for (i = 0; i < MAX - 1; i++) {
		j = i + 1;
		while (j < MAX) {
			if (numbers[i] < numbers[j]) {
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
			j++;
		}
	}
}
/*
�Լ���: Output
��  ��: ������ ����Ϳ� ����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Output(ULong(*numbers)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%d ", numbers[i]);
	}
}