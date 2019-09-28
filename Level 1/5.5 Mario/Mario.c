/*
���ϸ�: Mario.c
��  ��: �������� ���� 10���� ���� ������ �� �� 100���� ������ �� ����� ������ �򵵷� �ϴ� ���α׷�
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 10
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*mushrooms));
ULong Mario(ULong(*mushrooms));
void Output(ULong score);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong mushrooms[MAX];
	ULong score;
	//ȣ��
	Input(mushrooms);
	score = Mario(mushrooms);
	Output(score);

	return 0;
}
/*
�Լ���: Input
��  ��: �������� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ������
*/
void Input(ULong(*mushrooms)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", mushrooms + i);
	}
}
/*
�Լ���: Mario
��  ��: �������� ���� �� ������ ���Ͽ� ����Ѵ�.
��  ��: ������
��  ��: ����
*/
ULong Mario(ULong(*mushrooms)) {
	ULong score = 0;
	ULong beforeScore;
	ULong afterScore;
	ULong beforeGap;
	ULong afterGap;
	ULong i;

	for (i = 0; i < MAX; i++) {
		beforeScore = score;
		afterScore = beforeScore + mushrooms[i];
		if (beforeScore < 100) {
			beforeGap = 100 - beforeScore;
		}
		else {
			beforeGap = beforeScore - 100;
		}
		if (afterScore < 100) {
			afterGap = 100 - afterScore;
		}
		else {
			afterGap = afterScore - 100;
		}
		if (afterGap <= beforeGap) {
			score = afterScore;
		}
	}
	return score;
}
/*
�Լ���: Output
��  ��: ������ ����Ϳ� ����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Output(ULong score) {
	printf("%d\n", score);
}
