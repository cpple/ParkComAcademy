/*
���ϸ�: Evaluate.c
��  ��: �л����� ������ �Է¹޾� ����, ���, �򰡿� ���񺰷� ����� ���Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.30
*/
#include<stdio.h>
#include<stdlib.h>
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
	char(*evaluation);
}Student;

//�����
int main(int argc, char* argv[]);
void Load(Student*(*students), ULong *count);
void Evaluate(Student(*students), ULong count, float *koreanAverage, float *englishAverage, float *mathAverage);
void Save(Student(*students), ULong count, float koreanAverage, float englishAverage, float mathAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	Student(*students);
	ULong count;
	float koreanAverage;
	float englishAverage;
	float mathAverage;
	//ȣ��
	Load(&students, &count);
	Evaluate(students, count, &koreanAverage, &englishAverage, &mathAverage);
	Save(students, count, koreanAverage, englishAverage, mathAverage);
	if (students != NULL) {
		free(students);
	}
	return 0;
}
/*
�Լ���: Load
��  ��: �л��� ��ũ ������ �����Ѵ�.
��  ��: ����
��  ��: �л���, ����
*/
void Load(Student*(*students), ULong *count) {
	Student student;
	ULong i = 0;

	FILE* file = fopen("Students.txt", "rt");
	*count = 0;
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		while (!feof(file)) {
			(*count)++;
			fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		}
		if (*count > 0) {
			*students = (Student(*))calloc(*count, sizeof(Student));
		}
		fseek(file, 0L, SEEK_SET);
		fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		while (!feof(file)) {
			(*students)[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, &student.koreanScore, &student.englishScore, &student.mathScore);
		}
		fclose(file);
	}
}
/*
�Լ���: Evaluate
��  ��: �л� ������ �Է¹޾� ����, ���, �򰡸� �߰��ϰ� ���񺰷� ����� ���Ѵ�.
��  ��: �л���, ����
��  ��: �л���, �������, �������, �������
*/
void Evaluate(Student(*students), ULong count, float *koreanAverage, float *englishAverage, float *mathAverage) {
	ULong i = 0;
	ULong koreanSum = 0;
	ULong englishSum = 0;
	ULong mathSum = 0;

	while (i < count) {
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
		i++;
	}
	*koreanAverage = koreanSum / (count*1.0F);
	*englishAverage = englishSum / (count*1.0F);
	*mathAverage = mathSum / (count*1.0F);
}
/*
�Լ���: Save
��  ��: �л��� ��ũ ������ �����Ѵ�.
��  ��: �л���, ����, �������, �������, �������
��  ��: ����
*/
void Save(Student(*students), ULong count, float koreanAverage, float englishAverage, float mathAverage) {
	ULong i = 0;

	FILE* file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=================================================================\n");
		fprintf(file, "����\t��������\t��������\t��������\t����\t���\t��\n");
		fprintf(file, "-----------------------------------------------------------------\n");
		while (i < count) {
			fprintf(file, "%s\t%d\t%d\t%d\t%d\t%.1f\t%s\n", students[i].name, students[i].koreanScore, students[i].englishScore, students[i].mathScore,
				students[i].sum, students[i].average, students[i].evaluation);
			i++;
		}
		fprintf(file, "=================================================================\n");
		fprintf(file, "�������: %.1f\n�������: %.1f\n�������: %.1f\n", koreanAverage, englishAverage, mathAverage);
		fclose(file);
	}
}