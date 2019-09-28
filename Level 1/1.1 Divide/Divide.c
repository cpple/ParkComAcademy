/*
���ϸ�: Divide.c
��  ��: �� �ڿ����� �Է¹޾� ���� ���� ���� ���� ������ �� ��� �������� ���Ѵ�.
�ۼ���: ������
�ۼ���: 2019.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2);
void Divide(ULong number1, ULong number2, ULong *quotient, ULong *remainder);
void Output(ULong quotient, ULong remainder);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong quotient;
	ULong remainder;
	//�Լ� ȣ��
	Input(&number1, &number2);
	Divide(number1, number2, &quotient, &remainder);
	Output(quotient, remainder);

	return 0;
}
/*
�Լ���: Input
��  ��: �� �ڿ����� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��1, ��2
*/
void Input(ULong *number1, ULong *number2) {
	scanf("%d %d", number1, number2);
}
/*
�Լ���: Divide
��  ��: �Է¹��� �� ���� ���� ���� ��� �������� ���Ѵ�.
��  ��: ��1, ��2
��  ��: ��, ������
*/
void Divide(ULong number1, ULong number2, ULong *quotient, ULong *remainder) {
	*quotient = number1 / number2;
	*remainder = number1 % number2;
}
/*
�Լ���: Output
��  ��: ��� �������� ����Ϳ� ����Ѵ�.
��  ��: ��, ������
��  ��: ����
*/
void Output(ULong quotient, ULong remainder) {
	printf("��: %d, ������: %d\n", quotient, remainder);
}
