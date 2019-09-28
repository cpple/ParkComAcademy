/*
���ϸ�: PackSugar
��  ��: ������ ���Ը� �Է¹޾� 5kg ���ڿ� 3kg���ڿ� ���� �� ���� �� ��� �����ϴ� �ּ� ���ڼ��� 5kg���� ��, 3kg���� ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
void PackSugar(ULong weight, ULong *leastBoxes, ULong *boxes3, ULong *boxes5);
void Output(ULong leastBoxes, ULong boxes3, ULong boxes5);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong weight;
	ULong leastBoxes;
	ULong boxes3;
	ULong boxes5;
	//ȣ��
	weight = Input();
	PackSugar(weight, &leastBoxes, &boxes3, &boxes5);
	Output(leastBoxes, boxes3, boxes5);

	return 0;
}
/*
�Լ���: Input
��  ��: ������ ���Ը� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����
*/
ULong Input() {
	ULong weight;
	scanf("%d", &weight);
	return weight;
}
/*
�Լ���: PackSugar
��  ��: ���Կ� ���� 5kg����, 3kg���ڿ� ������ �� ������� �����ϵ� ���ڸ� �ּ������� ������ �� ���� ���ڸ� ��� �ϴ��� ���Ͽ� ����Ѵ�.
��  ��: ����
��  ��: �ּһ��ڼ�, 5kg���ڼ�, 3kg���ڼ�
*/
void PackSugar(ULong weight, ULong *leastBoxes, ULong *boxes5, ULong *boxes3) {
	ULong leftWeight;

	*boxes5 = weight / 5;
	leftWeight = weight - (*boxes5 * 5);
	*boxes3 = leftWeight / 3;
	leftWeight = leftWeight - (*boxes3 * 3);
	while ((leftWeight > 0 && leftWeight < 3) && *boxes5 > 0) {
		(*boxes5)--;
		leftWeight = weight - (*boxes5 * 5);
		*boxes3 = leftWeight / 3;
		leftWeight = leftWeight - (*boxes3 * 3);
	}
	if (leftWeight == 0) {
		*leastBoxes = *boxes5 + *boxes3;
	}
	else {
		*leastBoxes = 0;
	}
}
/*
�Լ���: Output
��  ��: �ּһ��ڼ�, 5kg���ڼ�, 3kg���ڼ��� ����Ϳ� ����Ѵ�.
��  ��: �ּһ��ڼ�, 5kg���ڼ�, 3kg���ڼ�
��  ��: ����
*/
void Output(ULong leastBoxes, ULong boxes5, ULong boxes3) {
	if (leastBoxes != 0) {
		printf("%d\n%d %d\n", leastBoxes, boxes5, boxes3);
	}
	else {
		printf("-1\n");
	}
}