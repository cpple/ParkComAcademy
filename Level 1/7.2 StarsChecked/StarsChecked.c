/*
���ϸ�: StarsChecked.c
��  ��: ����� üũ���� ����� ����� ����Ѵ�.
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
��  ��: ����� üũ���� ����� �����.
��  ��: ����
��  ��: ����
*/
void Stars(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;
	ULong remainder1;
	ULong remainder2;

	for (row = 0; row < ROWS; row++) {
		remainder1 = row % 2;
		for (column = 0; column < COLUMNS; column++) {
			remainder2 = column % 2;
			if (remainder2 == remainder1) {
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
��  ��: ������ ����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Output(char(*stars)[COLUMNS]) {
	ULong row;
	ULong column;

	for (row = 0; row < ROWS; row++) {
		for (column = 0; column < COLUMNS; column++) {
			printf("%c ", stars[row][column]);
		}
		printf("\n");
	}
}