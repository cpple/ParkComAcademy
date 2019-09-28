/*
���ϸ�: SumDigit.c
��  ��: ���� �Է¹޾� �ڸ����� ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.17
*/
//��ó����
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
ULong SumDigit(ULong number);
void Output(ULong sum);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number;
	ULong sum;
	//�Լ� ȣ��
	number = Input();
	sum = SumDigit(number);
	Output(sum);

	return 0;
}
/*
�Լ���: Input
��  ��: ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
�Լ���: SumDigit
��  ��: ���� �Է¹޾� �ڸ����� ���� ���Ͽ� ����Ѵ�.
��  ��: ��
��  ��: ��
*/
ULong SumDigit(ULong number) {
	ULong sum = 0;
	ULong digitNumber;
	ULong dividend;

	dividend = number;
	while (dividend > 0) {
		digitNumber = dividend % 10;
		sum += digitNumber;
		dividend /= 10;
	}
	return sum;
}
/*
�Լ���: Output
��  ��: ����Ϳ� ���� ����Ѵ�.
��  ��: ��
��  ��: ����
*/
void Output(ULong sum) {
	printf("�ڸ��� ��: %d\n", sum);
}