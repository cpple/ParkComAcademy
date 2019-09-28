/*
���ϸ�: Wage.c
��  ��: ������� ����, �۾��ð�, �ڵ带 �Է¹޾� �ӱ��� ����� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.25
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(char(*names)[11], ULong(*times), ULong(*codes));
void Wage(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages));
void Output(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages));

//���Ǻ�
int main(int argc, char* argv[]) {
	char names[MAX][11];
	ULong times[MAX];
	ULong codes[MAX];
	ULong wages[MAX];
	//ȣ��
	Input(names, times, codes);
	Wage(names, times, codes, wages);
	Output(names, times, codes, wages);

	return 0;
}
/*
�Լ���: Input
��  ��: �����, �۾��ð���, �ڵ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �����, �۾��ð���, �ڵ��
*/
void Input(char(*names)[11], ULong(*times), ULong(*codes)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%s %d %d", names[i], times + i, codes + i);
	}
}
/*
�Լ���: Wage
��  ��: �Է¹��� ������� �ӱ��� ����Ѵ�.
��  ��: �����, �۾��ð���, �ڵ��
��  ��: �ӱݵ�
*/
void Wage(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages)) {
	ULong hourWage;
	ULong i;

	for (i = 0; i < MAX; i++) {
		if (codes[i] >= 1 && codes[i] <= 4) {
			switch (codes[i]) {
			case 1: hourWage = 2000; break;
			case 2: hourWage = 2500; break;
			case 3: hourWage = 3000; break;
			case 4: hourWage = 4000; break;
			default: break;
			}
		}
		else {
			hourWage = 0;
		}
		wages[i] = times[i] * hourWage;
	}
}
/*
�Լ���: Output
��  ��: �����, �۾��ð���, �ڵ��, �ӱݵ��� ����Ϳ� ����Ѵ�.
��  ��: �����, �۾��ð���, �ڵ��, �ӱݵ�
��  ��: ����
*/
void Output(char(*names)[11], ULong(*times), ULong(*codes), ULong(*wages)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		printf("%s %d %d %d\n", names[i], times[i], codes[i], wages[i]);
	}
}