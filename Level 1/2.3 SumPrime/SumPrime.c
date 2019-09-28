/*
���ϸ�: SumPrime.c
��  ��: �� ���� �Է¹޾� �� ������ �� �� �Ҽ����� ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2);
ULong SumPrime(ULong number1, ULong number2);
void Output(ULong sum);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong sum;
	//ȣ��
	Input(&number1, &number2);
	sum = SumPrime(number1, number2);
	Output(sum);

	return 0;
}
/*
�Լ���: Input
��  ��: �� ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��1, ��2
*/
void Input(ULong *number1, ULong *number2) {
	scanf("%d %d", number1, number2);
}
/*
�Լ���: SumPrime
��  ��: �� �� ������ �� �� �Ҽ��� ���� ���Ͽ� ����Ѵ�.
��  ��: ��1, ��2
��  ��: ��
*/
ULong SumPrime(ULong number1, ULong number2) {
	ULong sum = 0;
	ULong i;
	ULong j;
	ULong count;
	ULong remainder;

	i = number1;
	while (i <= number2) {
		count = 0;
		j = 2;
		while (j < i) {
			remainder = i % j;
			if (remainder == 0) {
				count++;
			}
			j++;
		}
		if (count == 0) {
			sum += i;
		}
		i++;
	}
	return sum;
}
/*
�Լ���: Output
��  ��: ���� ����Ϳ� ����Ѵ�.
��  ��: ��
��  ��: ����
*/
void Output(ULong sum) {
	printf("�Ҽ��� ��:%d\n", sum);
}

