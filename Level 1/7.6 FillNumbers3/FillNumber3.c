/*
���ϸ�: FillNumbers3.c
��  ��: �߰����� �� ���� ���� ���� �����ϴ� ������ ����� ����Ѵ�.
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
��  ��: �߰����� �� ���� ���� ���� �����ϴ� ������ �����.
��  ��: ����
��  ��: ����
*/
void FillNumbers(Long(*numbers)[COLUMNS]) {
	Long number;
	Long row;
	Long column;
	Long middle;
	Long pairIndex;

	middle = ROWS / 2;
	for (row = 0; row < ROWS; row++) {
		pairIndex = (ROWS - 1) - row;
		for (column = 0; column < COLUMNS; column++) {
			if ((column < middle - row || column > middle + row) || (column < middle - pairIndex || column > middle + pairIndex)) {
				number = 0;
				numbers[row][column] = number;
			}
			else if (column <= middle) {
				number++;
				numbers[row][column] = number;
			}
			else {
				number--;
				numbers[row][column] = number;
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
			printf("%d ", numbers[row][column]);
		}
		printf("\n");
	}
}
