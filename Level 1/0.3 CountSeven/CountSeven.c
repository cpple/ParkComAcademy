/*
���ϸ�: CountSeven
��  ��: 1���� 10000���� 7�� ������ ���� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.17
*/
#include<stdio.h>
#define MAX 10000
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong CountSeven();
void Output(ULong countSeven);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong countSeven;
	//�Լ� ȣ��
	countSeven = CountSeven();
	Output(countSeven);

	return 0;
}
/*
�Լ���: CountSeven
��  ��: 1���� 10000���� 7�� ������ ���� ����Ѵ�.
��  ��: ����
��  ��: 7�� ����
*/
ULong CountSeven() {
	ULong countSeven = 0;
	ULong number;
	ULong digitNumber;
	ULong dividend;

	for (number = 1; number <= MAX; number++) {
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			if (digitNumber == 7) {
				countSeven++;
			}
			dividend /= 10;
		}
	}
	return countSeven;
}
/*
�Լ���: Output
��  ��: 7�� ������ ����Ϳ� ����Ѵ�.
��  ��: 7�� ����
��  ��: ����
*/
void Output(ULong countSeven) {
	printf("1���� %d���� 7�� ������ %d���̴�.\n", MAX, countSeven);
}
