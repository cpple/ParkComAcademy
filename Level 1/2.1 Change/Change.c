/*
���ϸ�: Change.c
��  ��: ���ǰ��� �Է¹޾� �Ž������� ��� ��� ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.21
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
void Change(ULong price, ULong *count500, ULong *count100, ULong *count50, ULong *count10);
void Output(ULong count500, ULong count100, ULong count50, ULong count10);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong price;
	ULong count500;
	ULong count100;
	ULong count50;
	ULong count10;
	//ȣ��
	price = Input();
	Change(price, &count500, &count100, &count50, &count10);
	Output(count500, count100, count50, count10);

	return 0;
}
/*
�Լ���: Input
��  ��: ������ �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ����
*/
ULong Input() {
	ULong price;
	scanf("%d", &price);
	return price;
}
/*
�Լ���: Change
��  ��: �Ž������� ��� ��� �ϴ��� �������� ������ ���Ѵ�.
��  ��: ����
��  ��: 500������, 100������, 50������, 10������
*/
void Change(ULong price, ULong *count500, ULong *count100, ULong *count50, ULong *count10) {
	ULong change;
	ULong money = 0;
	*count500 = 0;
	*count100 = 0;
	*count50 = 0;
	*count10 = 0;
	
	while (money < price) {
		money += 1000;
	}change = money - price;
	while (change >= 500) {
		*count500= *count500 +1;
		change -= 500;
	}
	while (change >= 100) {
		*count100 = *count100 + 1;
		change -= 100;
	}
	while (change >= 50) {
		*count50 = *count50 + 1;
		change -= 50;
	}
	while (change > 0) {
		*count10 = *count10 + 1;
		change -= 10;
	}
}
/*
�Լ���: Output
��  ��: ������ ������ ����Ϳ� ����Ѵ�.
��  ��: 500������, 100������, 50������, 10������
��  ��: ����
*/
void Output(ULong count500, ULong count100, ULong count50, ULong count10) {
	printf("500�� ����: %d\n100�� ����: %d\n50�� ����: %d\n10�� ����: %d\n", count500, count100, count50, count10);
}
