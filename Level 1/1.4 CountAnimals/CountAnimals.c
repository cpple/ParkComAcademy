/*
���ϸ�: CountAnimals.c
��  ��: �� ������ �Ӹ� ���� �ٸ� ���� �Է¹޾� �� �� �������� ���Ƹ��� ���� �� �������� ���Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef signed long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong *heads, ULong *legs);
void CountAnimals(ULong heads, ULong legs, ULong *countDogs, ULong *countChicks);
void Output(ULong countDogs, ULong countChicks);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong heads;
	ULong legs;
	ULong countDogs;
	ULong countChicks;
	//ȣ��
	Input(&heads, &legs);
	CountAnimals(heads, legs, &countDogs, &countChicks);
	Output(countDogs, countChicks);

	return 0;
}
/*
�Լ���: Input
��  ��: �Ӹ� ���� �ٸ� ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �Ӹ� ��, �ٸ� ��
*/
void Input(ULong *heads, ULong *legs) {
	scanf("%d %d", heads, legs);
}
/*
�Լ���: CountAnimals
��  ��: �Է¹��� �Ӹ� ���� �ٸ� ���� �´� �������� ���Ƹ� ���� ���Ѵ�.
��  ��: �Ӹ� ��, �ٸ� ��
��  ��: ������ ��, ���Ƹ� ��
*/
void CountAnimals(ULong heads, ULong legs, ULong *countDogs, ULong *countChicks){
	ULong legSum;
	*countDogs = 0;
	*countChicks = heads - *countDogs;
	legSum = *countDogs * 4 + *countChicks * 2;
	while (legSum < legs) {
		(*countDogs)++;
		*countChicks = heads - *countDogs;
		legSum = *countDogs * 4 + *countChicks * 2;
	}
	if (*countDogs > heads) {
		*countDogs = 0;
		*countChicks = 0;
	}
}
/*
�Լ���: Output
��  ��: �������� ���Ƹ� ���� ����Ϳ� ����Ѵ�.
��  ��: ������ ��, ���Ƹ� ��, �ٸ� ��, �ٸ� ��
��  ��: ����
*/
void Output(ULong countDogs, ULong countChicks) {
	if(countDogs!=0 || countChicks!=0){
		printf("������ ��: %d ���Ƹ� ��: %d\n", countDogs, countChicks);
	}
	else {
		printf("0\n");
	}
}