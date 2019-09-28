/*
���ϸ�: GetPalindromicNumber.c
��  ��: ���� �Է¹޾� ȸ������ ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
ULong GetPalindromicNumber(ULong number);
void Output(ULong number);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number;
	//�Լ� ȣ��
	number = Input();
	number = GetPalindromicNumber(number);
	Output(number);

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
�Լ���: GetPalindromicNumber
��  ��: ���� �Է¹޾� ȸ������ ���Ͽ� ����Ѵ�.
��  ��: ��
��  ��: ��(ȸ��)
*/
ULong GetPalindromicNumber(ULong number) {
	ULong reversedNumber=0;
	ULong dividend;
	ULong digitNumber;

	while (reversedNumber != number) {
		number += reversedNumber;
		reversedNumber = 0;
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			reversedNumber = reversedNumber * 10 + digitNumber;
			dividend /= 10;
		}
	}
	return number;
}
/*
�Լ���: Output
��  ��: ��(ȸ��)�� ����Ϳ� ����Ѵ�.
��  ��: ��
��  ��: ����
*/
void Output(ULong number) {
	printf("�������� ȸ����: %d\n", number);
}
