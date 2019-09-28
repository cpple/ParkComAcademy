/*
���ϸ�: Average.c
��  ��: �л����� ����, 3���� ������ �Է¹޾� ������հ� ������� ���Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.25
*/
#include<stdio.h>
#define STUDENTS 5
#define SUBJECTS 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(char(*names)[11], ULong(*scores)[SUBJECTS]);
void Average(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float *classAverage);
void Output(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float classAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	char names[STUDENTS][11];
	ULong scores[STUDENTS][SUBJECTS];
	float averages[STUDENTS];
	float classAverage;
	//ȣ��
	Input(names, scores);
	Average(names, scores, averages, &classAverage);
	Output(names, scores, averages, classAverage);

	return 0;
}
/*
�Լ���: Input
��  ��: �����, �������� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �����, ������
*/
void Input(char(*names)[11], ULong(*scores)[SUBJECTS]) {
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		scanf("%s %d %d %d", names[i], scores[i] + 0, scores[i] + 1, scores[i] + 2);
	}
}
/*
�Լ���: Average
��  ��: �л����� 3���� ������ ��������� ���ϰ� ����ձ��� ���Ͽ� ����Ѵ�.
��  ��: �����, ������
��  ��: ��յ�, �����
*/
void Average(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float *classAverage) {
	ULong i;
	ULong j;
	ULong sum;
	ULong classSum = 0;

	for (i = 0; i < STUDENTS; i++) {
		sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			sum += scores[i][j];
			classSum += scores[i][j];
		}
		averages[i] = sum / (SUBJECTS*1.0F);
	}
	*classAverage = classSum / (STUDENTS*SUBJECTS*1.0F);
}
/*
�Լ���: Output
��  ��: �����, ������, ��յ�, ������� ����Ϳ� ����Ѵ�.
��  ��: �����, ������, ��յ�, �����
��  ��: ����
*/
void Output(char(*names)[11], ULong(*scores)[SUBJECTS], float(*averages), float classAverage) {
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		printf("%s %d %d %d %.1f\n", names[i], scores[i][0], scores[i][1], scores[i][2], averages[i]);
	}
	printf("%.1f\n", classAverage);
}