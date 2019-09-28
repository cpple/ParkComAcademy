/*
���ϸ�: HitandBlow.c
��  ��: ����� 4���� ��ȼ� 4���� �Է¹޾� ���� ��ġ�� ���� �� Hit, ���� ������ ��ġ�� �ٸ� �� Blow�� ������ �� ������ ���� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.22
*/
#include<stdio.h>
#define MAX 4
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*rightAnswers), ULong(*answers));
void HitandBlow(ULong(*rightAnswers), ULong(*answers), ULong *countHit, ULong *countBlow);
void Output(ULong countHit, ULong countBlow);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong rightAnswers[MAX];
	ULong answers[MAX];
	ULong countHit;
	ULong countBlow;
	//ȣ��
	Input(rightAnswers, answers);
	HitandBlow(rightAnswers, answers, &countHit, &countBlow);
	Output(countHit, countBlow);

	return 0;
}
/*
�Լ���: Input
��  ��: �������� ��ȼ����� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �������, ��ȼ���
*/
void Input(ULong(*rightAnswers), ULong(*answers)) {
	ULong i;
	printf("�������: ");
	for (i = 0; i < MAX; i++) {
		scanf("%d", rightAnswers + i);
	}
	printf("��ȼ���: ");
	for (i = 0; i < MAX; i++) {
		scanf("%d", answers + i);
	}
}
/*
�Լ���: HitandBlow
��  ��: �������� ��ȼ����� ���ؼ� ���� ��ġ�� ������ Hit, ���� ������ Blow�� ������ ������ ����.
��  ��: �������, ��ȼ���
��  ��: ��Ʈ����, ��ΰ���
*/
void HitandBlow(ULong(*rightAnswers), ULong(*answers), ULong *countHit, ULong *countBlow) {
	ULong i;
	ULong j;
	*countHit = 0;
	*countBlow = 0;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (answers[i] == rightAnswers[j]) {
				if (i == j) {
					(*countHit)++;
				}
				else {
					(*countBlow)++;
				}
			}
		}
	}
}
/*
�Լ���: Output
��  ��: ��Ʈ������ ��ΰ����� ����Ϳ� ����Ѵ�.
��  ��: ��Ʈ����, ��ΰ���
��  ��: ����
*/
void Output(ULong countHit, ULong countBlow) {
	printf("Hit����: %d Blow����: %d\n", countHit, countBlow);
}
