/*
���ϸ�: PutTiles.c
��  ��: ���� ����, ������ ���̸� �Է¹޾� 8*8Ÿ���� �� ��, ������ Ÿ�� ���� �߶� Ÿ�� ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.21
*/
#include<stdio.h>
#define TILE 8
#pragma warning (disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong *width, ULong *height);
void PutTiles(ULong width, ULong height, ULong *tiles, ULong *cutTiles);
void Output(ULong tiles, ULong cutTiles);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong width;
	ULong height;
	ULong tiles;
	ULong cutTiles;
	//ȣ��
	Input(&width, &height);
	PutTiles(width, height, &tiles, &cutTiles);
	Output(tiles, cutTiles);

	return 0;
}
/*
�Լ���: Input
��  ��: ���� ���ο� ���� ���̸� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����, ����
*/
void Input(ULong *width, ULong *height) {
	scanf("%d %d", width, height);
}
/*
�Լ���: PutTiles
��  ��: �濡 Ÿ���� �� �� ����� ������ Ÿ�� ���� �߶� Ÿ�� ���� ���Ͽ� ����Ѵ�.
��  ��: ����, ����
��  ��: ������ Ÿ�� ��, �߶� Ÿ�� ��
*/
void PutTiles(ULong width, ULong height, ULong *tiles, ULong *cutTiles) {
	ULong rowTiles;
	ULong lineTiles;
	ULong emptyRow;
	ULong emptyLine;

	rowTiles = width / TILE;
	lineTiles = height / TILE;
	*tiles = rowTiles * lineTiles;
	emptyRow = width % TILE;
	emptyLine = height % TILE;
	if (emptyRow != 0 && emptyLine != 0) {
		*cutTiles = rowTiles + lineTiles + 1;
	}
	else if (emptyRow != 0) {
		*cutTiles = lineTiles;
	}
	else if (emptyLine != 0) {
		*cutTiles = rowTiles;
	}
	else {
		*cutTiles = 0;
	}
}
/*
�Լ���: Output
��  ��: ������ Ÿ�� ���� �߶� Ÿ�� ���� ����Ϳ� ����Ѵ�.
��  ��: ������ Ÿ�� ��, �߶� Ÿ�� ��
��  ��: ����
*/
void Output(ULong tiles, ULong cutTiles) {
	printf("������ Ÿ�� ��: %d\n�߶� Ÿ�� ��: %d\n", tiles, cutTiles);
}
