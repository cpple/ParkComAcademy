/*
���ϸ�: Descend.c
��  ��: �� ������ �Է¹޾� ������������ ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong *number1, ULong *number2, ULong *number3);
void Descend(ULong number1, ULong number2, ULong number3, ULong *biggest, ULong *middle, ULong *smallest);
void Output(ULong biggest, ULong middle, ULong smallest);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number1;
	ULong number2;
	ULong number3;
	ULong biggest;
	ULong middle;
	ULong smallest;
	//ȣ��
	Input(&number1, &number2, &number3);
	Descend(number1, number2, number3, &biggest, &middle, &smallest);
	Output(biggest, middle, smallest);

	return 0;
}
/*
�Լ���: Input
��  ��: �� ������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��1, ��2, ��3
*/
void Input(ULong *number1, ULong *number2, ULong *number3) {
	scanf("%d %d %d", number1, number2, number3);
}
/*
�Լ���: Descend
��  ��: �� ���� ������������ �����Ѵ�.
��  ��: ��1, ��2, ��3
��  ��: ū��, �߰���, ������
*/
void Descend(ULong number1, ULong number2, ULong number3, ULong *biggest, ULong *middle, ULong *smallest) {
	if (number1 > number2) {
		if (number1 > number3) {
			if (number2 > number3) {
				*biggest = number1;
				*middle = number2;
				*smallest = number3;
			}
			else {
				*biggest = number1;
				*middle = number3;
				*smallest = number2;
			}
		}
		else {
			*biggest = number3;
			*middle = number1;
			*smallest = number2;
		}
	}
	else {
		if (number2 > number3) {
			if (number1 > number3) {
				*biggest = number2;
				*middle = number1;
				*smallest = number3;
			}
			else {
				*biggest = number2;
				*middle = number3;
				*smallest = number1;
			}
		}
		else {
			*biggest = number3;
			*middle = number2;
			*smallest = number1;
		}
	}
}
/*
�Լ���: Output
��  ��: ū ��, �߰���, �������� ����Ϳ� ����Ѵ�.
��  ��: ū��, �߰���, ������
��  ��: ����
*/
void Output(ULong biggest, ULong middle, ULong smallest) {
	printf("%d %d %d\n", biggest, middle, smallest);
}
