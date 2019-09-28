/*
���ϸ�: ReverseArray.c
��  ��: ������ �Է¹޾� �Ųٷ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.22
*/
#include<stdio.h>
#define MAX 1000
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
void Input(Long *countNumber, Long(*numbers));
void ReverseArray(Long countNumber, Long(*numbers));
void Output(Long countNumber, Long(*numbers));

//���Ǻ�
int main(int argc, char* argv[]) {
	Long countNumber;
	Long numbers[MAX];
	//ȣ��
	Input(&countNumber, numbers);
	ReverseArray(countNumber, numbers);
	Output(countNumber, numbers);

	return 0;
}
/*
�Լ���: Input
��  ��: ���� ������ �� ������ŭ�� ������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ���� ����, ����
*/
void Input(Long *countNumber, Long(*numbers)) {
	Long i = 0;
	printf("���� ����: ");
	scanf("%d", countNumber);
	printf("����\n");
	while (i < *countNumber) {
		scanf("%d", numbers + i);
		i++;
	}
}
/*
�Լ���: ReverseArray
��  ��: ������ �Ųٷ� �����ؼ� ����Ѵ�.
��  ��: ���ǰ���, ����
��  ��: ����
*/
void ReverseArray(Long countNumber, Long(*numbers)) {
	Long i = 0;
	Long j;
	Long temp;
	j = countNumber-1;

	while (i < (countNumber / 2)) {
		temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		j--;
		i++;
	}
}
/*
�Լ���: Output
��  ��: ������ ����Ϳ� ����Ѵ�.
��  ��: ���ǰ���, ����
��  ��: ����
*/
void Output(Long countNumber, Long(*numbers)) {
	Long i = 0;
	while (i < countNumber) {
		printf("%d ", numbers[i]);
		i++;
	}
}
