/*
���ϸ�: Reverse.c
��  ��: ���� �Է¹޾� �� ���� ���������� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
ULong Reverse(ULong number);
void Output(ULong reversedNumber);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number;
	ULong reversedNumber;
	//�Լ� ȣ��
	number = Input();
	reversedNumber = Reverse(number);
	Output(reversedNumber);

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
�Լ���: Reverse
��  ��: ���� �Է¹޾� ������ ���� ���Ͽ� ����Ѵ�.
��  ��: ��
��  ��: ������ ��
*/
ULong Reverse(ULong number) {
	ULong reversedNumber = 0;
	ULong digitNumber;
	ULong dividend;

	dividend = number;
	while (dividend > 0) {
		digitNumber = dividend % 10;
		reversedNumber = reversedNumber * 10 + digitNumber;
		dividend /= 10;
	}
	return reversedNumber;
}
/*
�Լ���: Output
��  ��: ������ ���� ����Ϳ� ����Ѵ�.
��  ��: ������ ��
��  ��: ����
*/
void Output(ULong reversedNumber) {
	printf("������ ��: %d\n", reversedNumber);
}
