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
typedef struct _student {
	char name[11];
	ULong scores[SUBJECTS];
	float average;
}Student;

//�����
int main(int argc, char* argv[]);
void Load(Student(*students));
void Average(Student(*students), float *classAverage);
void Save(Student(*students), float classAverage);

//���Ǻ�
int main(int argc, char* argv[]) {
	Student students[STUDENTS];
	float classAverage;
	//ȣ��
	Load(students);
	Average(students, &classAverage);
	Save(students, classAverage);

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
	ULong i=0;

	FILE* file;
	file = fopen("Students.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d %d", student.name, &student.scores[0], &student.scores[1], &student.scores[2]);
		while (!feof(file)) {
			students[i] = student;
			i++;
			fscanf(file, "%s %d %d %d", student.name, &student.scores[0], &student.scores[1], &student.scores[2]);
		}
		fclose(file);
	}
}
/*
�Լ���: Average
��  ��: �л����� 3���� ������ ��������� ���ϰ� ����ձ��� ���Ͽ� ����Ѵ�.
��  ��: �л���
��  ��: �л���, �����
*/
void Average(Student (*students), float *classAverage) {
	ULong i;
	ULong j;
	ULong sum;
	ULong classSum = 0;

	for (i = 0; i < STUDENTS; i++) {
		sum = 0;
		for (j = 0; j < SUBJECTS; j++) {
			sum += students[i].scores[j];
			classSum += students[i].scores[j];
		}
		students[i].average = sum / (SUBJECTS*1.0F);
	}
	*classAverage = classSum / (STUDENTS*SUBJECTS*1.0F);
}
/*
�Լ���: Save
��  ��: �л���, ������� ��ũ ���Ͽ� �����Ѵ�.
��  ��: �л���, �����
��  ��: ����
*/
void Save(Student(*students), float classAverage) {
	ULong i;

	FILE* file;
	file = fopen("Students.txt", "wt");
	if (file != NULL) {
		fprintf(file, "=====================================\n");
		fprintf(file, "����\t������\t\t\t���\n");
		fprintf(file, "-------------------------------------\n");
		for (i = 0; i < STUDENTS; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\t%.1f\n", students[i].name, students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].average);
		}
		fprintf(file, "-------------------------------------\n");
		fprintf(file, "�����: %.1f\n", classAverage);
		fclose(file);
	}
}