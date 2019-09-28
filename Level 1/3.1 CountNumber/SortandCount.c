/*
���ϸ�: SortandCount.c
��  ��: ������ �Է¹޾� ���, ����, ¦��, Ȧ���� ������ ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.22
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
void Input(Long(*numbers));
void SortandCount(Long(*numbers), Long *positive, Long *negative, Long *even, Long *odd);
void Output(Long positive, Long negative, Long even, Long odd);

//���Ǻ�
int main(int argc, char* argv[]) {
	Long numbers[MAX];
	Long positive;
	Long negative;
	Long even;
	Long odd;
	//ȣ��
	Input(numbers);
	SortandCount(numbers, &positive, &negative, &even, &odd);
	Output(positive, negative, even, odd);

	return 0;
}
/*
�Լ���: Input
��  ��: �� 100���� �ܺ��Է¹޴´�.
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
�Լ���: SortandCount
��  ��: ���� �߿� ���, ����, ¦��, Ȧ���� ������ ����.
��  ��: ����
��  ��: �������, ��������, ¦������, Ȧ������
*/
void SortandCount(Long(*numbers), Long *positive, Long *negative, Long *even, Long *odd) {
	Long remainder;
	Long i;
	*positive = 0;
	*negative = 0;
	*even = 0;
	*odd = 0;

	for (i = 0; i < MAX; i++) {
		if (numbers[i] > 0) {
			(*positive)++;
			remainder = numbers[i] % 2;
			if (remainder == 0) {
				(*even)++;
			}
			else {
				(*odd)++;
			}
		}
		else if (numbers[i] < 0) {
			(*negative)++;
		}
	}
}
/*
�Լ���: Output
��  ��: ���, ����, ¦��, Ȧ���� ������ ����Ϳ� ����Ѵ�.
��  ��: �������, ��������, ¦������, Ȧ������
��  ��: ����
*/
void Output(Long positive, Long negative, Long even, Long odd) {
	printf("���:%d�� ����:%d�� ¦��:%d�� Ȧ��:%d��\n", positive, negative, even, odd);
}