/*
���ϸ�: Clap.c
��  ��: ������ ������ ���� ���鼭 3�� ����̰ų� 3�� ���� ���� �ڼ��� ġ�� 369������ �Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 1000
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
void Clap(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers));
void Output(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers));

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong lastNumber;
	ULong numbers[MAX];
	ULong clapNumbers[MAX];
	//ȣ��
	lastNumber = Input();
	Clap(lastNumber, numbers, clapNumbers);
	Output(lastNumber, numbers, clapNumbers);

	return 0;
}
/*
�Լ���: Input
��  ��: ������ ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��������
*/
ULong Input() {
	ULong lastNumber;
	scanf("%d", &lastNumber);
	return lastNumber;
}
/*
�Լ���: Clap
��  ��: ������ ������ ���� ���鼭 ����� �ڼ�ĥ ������ ���Ͽ� ����Ѵ�.
��  ��: ��������
��  ��: ����, �ڼ�ĥ����
*/
void Clap(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers)) {
	ULong remainder;
	ULong digitNumber;
	ULong number = 1;
	ULong i = 0;
	ULong j = 0;
	ULong countDigit;
	ULong dividend;

	while (number <= lastNumber) {
		remainder = number % 3;
		if (remainder == 0) {
			clapNumbers[i] = number;
			i++;
		}
		else {
			countDigit = 0;
			dividend = number;
			while (dividend > 0) {
				digitNumber = dividend % 10;
				if (digitNumber == 3) {
					countDigit++;
				}
				dividend /= 10;
			}
			if (countDigit >= 1) {
				clapNumbers[i] = number;
				i++;
			}
			else {
				numbers[j] = number;
				j++;
			}
		}
		number++;
	}
}
/*
�Լ���: Output
��  ��: ���� ���� �ڼ�ģ��.
��  ��: ��������, ����, �ڼ�ĥ����
��  ��: ����
*/
void Output(ULong lastNumber, ULong(*numbers), ULong(*clapNumbers)) {
	ULong number = 1;
	ULong i = 0;
	ULong j = 0;
	while (number <= lastNumber) {
		if (number == clapNumbers[i]) {
			printf("Clap ");
			i++;
		}
		else {
			printf("%d ", numbers[j]);
			j++;
		}
		number++;
	}
}