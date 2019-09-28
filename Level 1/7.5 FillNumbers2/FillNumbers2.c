/*
���ϸ�: FillNumbers2.c
��  ��: ���� ���鼭 �Ųٷ� �� ���ڸ� ����ؼ� �׸��� ������ ���� �迭�� �����.
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
��  ��: ���� ���鼭 �Ųٷ� �� ���ڸ� ����ؼ� �׸��� ������ ���� �迭�� �����.
��  ��: ����
��  ��: ����
*/
void FillNumbers(Long(*numbers)[COLUMNS]) {
	Long number = 1;
	Long row;
	Long column;
	Long i;
	Long remainder;

	for (i = 0; i < ROWS; i++) {
		remainder = i % 2;
		if (remainder == 0) {
			row = 0;
			column = i;
			while (row <= column) {
				numbers[row][column] = number;
				number++;
				row++;
			}
			row = i;
			column = i - 1;
			while (column >= 0) {
				numbers[row][column] = number;
				number++;
				column--;
			}
		}
		else {
			column = 0;
			row = i;
			while (column <= row) {
				numbers[row][column] = number;
				number++;
				column++;
			}
			column = i;
			row = i - 1;
			while (row >= 0) {
				numbers[row][column] = number;
				number++;
				row--;
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