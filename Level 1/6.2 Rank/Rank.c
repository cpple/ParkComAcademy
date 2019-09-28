/*
���ϸ�: Rank.c
��  ��: �л����� ������ ��ȣ������ �Էµ� �� ���� ������ ���Ͽ� ��ȣ, ����, ���� ������ ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*scores));
void Rank(ULong(*scores), ULong(*ranks));
void Output(ULong(*scores), ULong(*ranks));

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong scores[MAX];
	ULong ranks[MAX];
	//ȣ��
	Input(scores);
	Rank(scores, ranks);
	Output(scores, ranks);

	return 0;
}
/*
�Լ���: Input
��  ��: �������� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ������
*/
void Input(ULong(*scores)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", scores + i);
	}
}
/*
�Լ���: Rank
��  ��: �����鿡 ���� ���� ������ ���Ѵ�.
��  ��: ������
��  ��: ������
*/
void Rank(ULong(*scores), ULong(*ranks)) {
	ULong rank;
	ULong i;
	ULong j;

	for (i = 0; i < MAX; i++) {
		rank = 1;
		for (j = 0; j < MAX; j++) {
			if (scores[i] < scores[j]) {
				rank++;
			}
		}
		ranks[i] = rank;
	}
}
/*
�Լ���: Output
��  ��: ��ȣ���� ������ ������ ����Ϳ� ����Ѵ�.
��  ��: ������, ������
��  ��: ����
*/
void Output(ULong(*scores), ULong(*ranks)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%d %d %d\n", i + 1, scores[i], ranks[i]);
	}
}
