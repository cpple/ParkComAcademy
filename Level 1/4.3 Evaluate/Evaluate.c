/*
���ϸ�: Evaluate.c
��  ��: �л����� 3���� ������ �Է¹޾� ����, ���, �򰡸� ���ϰ� ���� ��� ���� ���Ѵ�.
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
void Input(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores));
void Evaluate(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float *koreanAverage, float *englishAverage, float *mathAverage);
void Output(char (*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float koreanAverage, float englishAverage, float mathAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	char names[STUDENTS][11];
	ULong koreanScores[STUDENTS];
	ULong englishScores[STUDENTS];
	ULong mathScores[STUDENTS];
	ULong sums[STUDENTS];
	float averages[STUDENTS];
	char* evaluations[STUDENTS];
	float koreanAverage;
	float englishAverage;
	float mathAverage;
	//ȣ��
	Input(names, koreanScores, englishScores, mathScores);
	Evaluate(names, koreanScores, englishScores, mathScores, sums, averages, evaluations, &koreanAverage, &englishAverage, &mathAverage);
	Output(names, koreanScores, englishScores, mathScores, sums, averages, evaluations, koreanAverage, englishAverage, mathAverage);

	return 0;
}
/*
�Լ���: Input
��  ��: �����, ����������, ����������, ������������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �����, ����������, ����������, ����������
*/
void Input(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores)) {
	ULong i;
	for (i = 0; i < STUDENTS; i++) {
		scanf("%s %d %d %d", names[i], koreanScores + i, englishScores + i, mathScores + i);
	}
}
/*
�Լ���: Evaluate
��  ��: �Է¹��� ������ ���� ����, ���, �򰡸� ���ϰ� ���񺰷� ����� ���Ͽ� ����Ѵ�.
��  ��: �����, ����������, ����������, ����������
��  ��: ������, ��յ�, �򰡵�, �������, �������, �������
*/
void Evaluate(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float *koreanAverage, float *englishAverage, float *mathAverage) {
	ULong koreanSum = 0;
	ULong englishSum = 0;
	ULong mathSum = 0;
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		sums[i] = koreanScores[i] + englishScores[i] + mathScores[i];
		averages[i] = sums[i] / (SUBJECTS*1.0F);
		if (averages[i] >= 90.0F) {
			evaluations[i] = "EXCELLENT";
		}
		else if (averages[i] < 60.0F) {
			evaluations[i] = "FAIL";
		}
		else {
			evaluations[i] = "";
		}
		koreanSum += koreanScores[i];
		englishSum += englishScores[i];
		mathSum += mathScores[i];
	}
	*koreanAverage = koreanSum / (STUDENTS*1.0F);
	*englishAverage = englishSum / (STUDENTS*1.0F);
	*mathAverage = mathSum / (STUDENTS*1.0F);
}
/*
�Լ���: Output
��  ��: �����, ����������, ����������, ����������, ������, ��յ�, �򰡵�, �������, �������, ��������� ����Ϳ� ����Ѵ�.
��  ��: �����, ����������, ����������, ����������, ������, ��յ�, �򰡵�, �������, �������, �������
��  ��: ����
*/
void Output(char(*names)[11], ULong(*koreanScores), ULong(*englishScores), ULong(*mathScores), ULong(*sums), float(*averages),
	char* (*evaluations), float koreanAverage, float englishAverage, float mathAverage) {
	ULong i;
	for (i = 0; i < STUDENTS; i++) {
		printf("%s %d %d %d %d %.1f %s\n", names[i], koreanScores[i], englishScores[i], mathScores[i], sums[i], averages[i], evaluations[i]);
	}
	printf("�������:%.1f\n�������:%.1f\n�������:%.1f\n", koreanAverage, englishAverage, mathAverage);
}