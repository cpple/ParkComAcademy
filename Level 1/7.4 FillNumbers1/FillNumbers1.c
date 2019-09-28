/*
���ϸ�: FillNumbers.c
��  ��: ���� ���鼭 5*5 �迭�� ���� ���·� ä���ִ´�.
�ۼ���: ������
�ۼ���: 19.1.24
*/
#include<stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
void FillNumbers(Long(*numbers)[COLUMNS]);
void Output(Long(*numbers)[COLUMNS]);

//���Ǻ�
int main(int argc, char* argv[]) {
	Long numbers[ROWS][COLUMNS];
	//ȣ��
	FillNumbers(numbers);
	Output(numbers);

	return 0;
}
/*
�Լ���: FillNumbers
��  ��: ���� ���鼭 ���� ���·� ä���־� ������ �����.
��  ��: ����
��  ��: ����
*/
void FillNumbers(Long(*numbers)[COLUMNS]) {
	Long number = 1;
	Long row;
	Long column;
	Long remainder;

	for (row = 0; row < ROWS; row++) {
		remainder = row % 2;
		if (remainder == 0) {
			for (column = 0; column < COLUMNS; column++) {
				numbers[row][column] = number;
				number++;
			}
		}
		else {
			for (column = COLUMNS - 1; column >= 0; column--) {
				numbers[row][column] = number;
				number++;
			}
		}
	}
}
/*
�Լ���: Output
��  ��: ������ ����Ϳ� ����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Output(Long(*numbers)[COLUMNS]) {
	Long row;
	Long column;

	for (row = 0; row < ROWS; row++) {
		for (column = 0; column < COLUMNS; column++) {
			printf("%2d ", numbers[row][column]);
		}
		printf("\n");
	}
}
