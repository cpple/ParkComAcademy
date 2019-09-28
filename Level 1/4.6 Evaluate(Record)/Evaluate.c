/*
���ϸ�: Evaluate.c
��  ��: �л����� 3���� ������ �Է¹޾� ����, ���, �򰡸� ���ϰ� ���� ��� ���� ���Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.28
*/
#include<stdio.h>
#define STUDENTS 5
#define SUBJECTS 3
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _student {
	char name[11];
	ULong koreanScore;
	ULong englishScore;
	ULong mathScore;
	ULong sum;
	float average;
	char* evaluation;
}Student;

//�����
int main(int argc, char* argv[]);
void Load(Student(*students));
void Evaluate(Student(*students), float *koreanAverage, float *englishAverage, float *mathAverage);
void Save(Student(*students), float koreanAverage, float englishAverage, float mathAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	Student students[STUDENTS];
	float koreanAverage;
	float englishAverage;
	float mathAverage;
	//ȣ��
	Load(students);
	Evaluate(students, &koreanAverage, &englishAverage, &mathAverage);
	Save(students, koreanAverage, englishAverage, mathAverage);

	return 0;
}
/*
�Լ���: Load
��  ��: �л� ��ũ ������ �����Ѵ�.
��  ��: ����
��  ��: �л���
*/
void Load(Student(*students)) {
	Student student;
	ULong i = 0;

	FILE* file;
	file = fopen("Students.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		while (!feof(file)) {
			students[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		}
		fclose(file);
	}
}
/*
�Լ���: Evaluate
��  ��: �Է¹��� ������ ���� ����, ���, �򰡸� ���ϰ� ���񺰷� ����� ���Ͽ� ����Ѵ�.
��  ��: �л���
��  ��: �л���, �������, �������, �������
*/
void Evaluate(Student (*students), float *koreanAverage, float *englishAverage, float *mathAverage) {
	ULong koreanSum = 0;
	ULong englishSum = 0;
	ULong mathSum = 0;
	ULong i;

	for (i = 0; i < STUDENTS; i++) {
		students[i].sum = students[i].koreanScore + students[i].englishScore + students[i].mathScore;
		students[i].average = students[i].sum / (SUBJECTS*1.0F);
		if (students[i].average >= 90.0F) {
			students[i].evaluation = "EXCELLENT";
		}
		else if (students[i].average < 60.0F) {
			students[i].evaluation = "FAIL";
		}
		else {
			students[i].evaluation = "";
		}
		koreanSum += students[i].koreanScore;
		englishSum += students[i].englishScore;
		mathSum += students[i].mathScore;
	}
	*koreanAverage = koreanSum / (STUDENTS*1.0F);
	*englishAverage = englishSum / (STUDENTS*1.0F);
	*mathAverage = mathSum / (STUDENTS*1.0F);
}
/*
�Լ���: Save
��  ��: �л���� �������, �������, ��������� ��ũ ���Ͽ� �����Ѵ�.
��  ��: �л���, �������, �������, �������
��  ��: ����
*/
void Save(Student(*students), float koreanAverage, float englishAverage, float mathAverage) {
	ULong i;

	FILE* file;
	file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================================================\n");
		fprintf(file, "����\t��������\t��������\t��������\t����\t���\t��\n");
		fprintf(file, "---------------------------------------------------------------------\n");
		for (i = 0; i < STUDENTS; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\t%d\t%.1f\t%s\n", students[i].name, students[i].koreanScore, students[i].englishScore, students[i].mathScore,
				students[i].sum, students[i].average, students[i].evaluation);
		}
		fprintf(file, "---------------------------------------------------------------------\n");
		fprintf(file, "�������: %.1f\n�������: %.1f\n�������: %.1f\n", koreanAverage, englishAverage, mathAverage);
		fclose(file);
	}
}