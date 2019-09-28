/*
���ϸ�: Average.c
��  ��: �л� ������ �Է¹޾� ������հ� ������� ����Ѵ�.
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
	ULong scores[SUBJECTS];
	ULong sum;
	float average;
}Student;
//�����
int main(int argc, char* argv[]);
void Load(Student*(*students), ULong *count);
void Average(Student(*students), ULong count, float *classAverage);
void Save(Student(*students), ULong count, float classAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	Student(*students);
	ULong count;
	float classAverage;
	//ȣ��
	Load(&students, &count);
	Average(students, count, &classAverage);
	Save(students, count, classAverage);
	if (students != NULL) {
		free(students);
	}
	return 0;
}
/*
�Լ���: Load
��  ��: �л��� ��ũ ������ �����Ѵ�
��  ��: ����
��  ��: �л���, ����
*/
void Load(Student*(*students), ULong *count) {
	Student student;
	ULong i = 0;

	FILE* file = fopen("Students.txt", "rt");
	*count = 0;
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		while (!feof(file)) {
			(*count)++;
			fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		}
		if (*count > 0) {
			*students = (Student(*))calloc(*count, sizeof(Student));
		}
		fseek(file, 0L, SEEK_SET);
		fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		while (!feof(file)) {
			(*students)[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, student.scores + 0, student.scores + 1, student.scores + 2);
		}
		fclose(file);
	}
}
/*
�Լ���: Average
��  ��: �л��� ������ �Է¹޾� ������հ� ������� ����Ѵ�.
��  ��: �л���, ����
��  ��: �л���, �����
*/
void Average(Student(*students), ULong count, float *classAverage) {
	ULong i = 0;
	ULong j;
	ULong classSum = 0;

	while (i < count) {
		students[i].sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			students[i].sum += students[i].scores[j];
			classSum += students[i].scores[j];
		}
		students[i].average = students[i].sum / (SUBJECTS + 1.0F);
		i++;
	}
	*classAverage = classSum / (count*SUBJECTS*1.0F);
}
/*
�Լ���: Save
��  ��: �л��� ��ũ ������ �����ϴ�.
��  ��: �л���, ����, �����
��  ��: ����
*/
void Save(Student(*students), ULong count, float classAverage) {
	ULong i = 0;

	FILE* file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================\n");
		fprintf(file, "����\t������\t\t\t����\t���\n");
		fprintf(file, "-------------------------------------\n");
		while (i < count) {
			fprintf(file, "%s\t%d\t%d\t%d\t%d\t%.1f\n", students[i].name, students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].sum, students[i].average);
			i++;
		}
		fprintf(file, "-------------------------------------\n");
		fprintf(file, "�����: %.1f\n", classAverage);
	}
}