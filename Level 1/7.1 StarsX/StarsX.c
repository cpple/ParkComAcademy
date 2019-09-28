/*
���ϸ�: StarsX.c
��  ��: ����� X����� ����� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.24
*/
#include<stdio.h>
#define ROWS 5
#define COLUMNS 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Stars(char(*stars)[COLUMNS]);
void Output(char(*stars)[COLUMNS]);

//���Ǻ�
int main(int argc, char* argv[]) {
	char stars[ROWS][COLUMNS];
	//ȣ��
	Stars(stars);
	Output(stars);

	return 0;
}
/*
�Լ���: Stars
��  ��: ����� X����� �����.
��  ��: ����
��  ��: ����
*/
void Stars(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;
	ULong pairIndex;

	for (row = 0; row < ROWS; row++) {
		pairIndex = (ROWS - 1) - row;
		for (column = 0; column < COLUMNS; column++) {
			if (column == row) {
				stars[row][column] = '*';
			}
			else if (column == pairIndex) {
				stars[row][column] = '*';
			}
			else {
				stars[row][column] = ' ';
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
void Output(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;

	for (row = 0; row < ROWS; row++) {
		for (column = 0; column < COLUMNS; column++) {
			printf("%c", stars[row][column]);
		}
		printf("\n");
	}
}