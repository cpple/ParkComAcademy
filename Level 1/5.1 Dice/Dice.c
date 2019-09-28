/*
���ϸ�: Dice.c
��  ��: �ֻ��� ���� ���� �Է¹ް� �� ���� ���� �Ǵ� �ֻ��� �� �� ���� ������ ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 6
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
Long Input();
void Dice(Long pipSum, Long(*firstPips), Long(*secondPips), Long *count);
void Output(Long(*firstPips), Long(*secondPips), Long count);

//���Ǻ�
int main(int argc, char* argv[]) {
	Long pipSum;
	Long firstPips[MAX];
	Long secondPips[MAX];
	Long count;
	//ȣ��
	pipSum = Input();
	Dice(pipSum, firstPips, secondPips, &count);
	Output(firstPips, secondPips, count);

	return 0;
}
/*
�Լ���: Input
��  ��: �������� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ������
*/
Long Input() {
	Long pipSum;
	scanf("%d", &pipSum);
	return pipSum;
}
/*
�Լ���: Dice
��  ��: ���� �տ� ���� �ֻ��� �� ���� ���� �� �ִ� ������ ������ ��� ���Ͽ� ����Ѵ�.
��  ��: ������
��  ��: ù��°����, �ι�°����, ����
*/
void Dice(Long pipSum, Long(*firstPips), Long(*secondPips), Long *count) {
	Long dice1 = 1;
	Long dice2;
	Long i = 0;
	*count = 0;

	while (dice1 <= MAX && dice1 < pipSum) {
		dice2 = pipSum - dice1;
		if (dice2 >= 1 && dice2 <= MAX) {
			firstPips[i] = dice1;
			secondPips[i] = dice2;
			i++;
			(*count)++; 
		}
		dice1++;
	}
}
/*
�Լ���: Output
��  ��: ù��° ����, �ι�° ������ ����Ϳ� ����Ѵ�.
��  ��: ù��° ����, �ι�° ����, ����
��  ��: ����
*/
void Output(Long(*firstPips), Long(*secondPips), Long count) {
	Long i = 0;
	while (i < count) {
		printf("%d %d\n", firstPips[i], secondPips[i]);
		i++;
	}
}