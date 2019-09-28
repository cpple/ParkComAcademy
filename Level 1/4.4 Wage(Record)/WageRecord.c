/*
���ϸ�: WageRecord.c
��  ��: ������� ����, �۾��ð�, �ڵ带 �Է¹޾� �ӱ��� ����� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.28
*/
#include<stdio.h>
#define MAX 5
#pragma warning(disable:4996)

typedef unsigned long int ULong;
typedef struct _worker {
	char name[11];
	ULong time;
	ULong code;
	ULong wage;
} Worker;

//�����
int main(int argc, char* argv[]);
void Load(Worker (*workers));
void Wage(Worker (*workers));
void Save(Worker (*workers));

//���Ǻ�
int main(int argc, char* argv[]) {
	Worker workers[MAX];
	//ȣ��
	Load(workers);
	Wage(workers);
	Save(workers);

	return 0;
}
/*
�Լ���: Load
��  ��: ��ũ ���� Workers.txt�� �д´�.
��  ��: ����
��  ��: �����
*/
void Load(Worker(*workers)) {
	Worker worker;
	ULong i=0;

	FILE* file;
	file = fopen("Workers.txt", "rt");
	if (file != NULL) {
		fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		while (!feof(file)) {
			workers[i] = worker;
			i++;
			fscanf(file, "%s %d %d", worker.name, &worker.time, &worker.code);
		}
	}
}
/*
�Լ���: Wage
��  ��: �Է¹��� ������� �ӱ��� ����Ѵ�.
��  ��: �����
��  ��: �����
*/
void Wage(Worker (*workers)) {
	ULong hourWage;
	ULong i;

	for (i = 0; i < MAX; i++) {
		if (workers[i].code >= 1 && workers[i].code <= 4) {
			switch (workers[i].code) {
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
		workers[i].wage = workers[i].time * hourWage;
	}
}
/*
�Լ���: Save
��  ��: ������� ��ũ ���Ͽ� �����Ѵ�.
��  ��: �����
��  ��: ����
*/
void Save(Worker(*workers)) {
	ULong i;
	FILE* file;

	file = fopen("Workers.txt", "wt");
	if (file != NULL) {
		fprintf(file, "%s", "=============================\n");
		fprintf(file, "%s", "����\t�۾��ð�\t�ڵ�\t�ӱ�\t\n");
		fprintf(file, "%s", "-----------------------------\n");
		for (i = 0; i < MAX; i++) {
			fprintf(file, "%s\t%d\t%d\t%d\n", workers[i].name, workers[i].time, workers[i].code, workers[i].wage);
		}
		fprintf(file, "%s", "=============================\n");
		fclose(file);
	}
}