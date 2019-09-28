/*
���ϸ�: GetBiggestNumber
��  ��: ���� �Է¹޾� �� ���� �ڸ����� �������� ���� �� �ִ� ���� ū ���� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.17
*/
#include<stdio.h>
#pragma warning(disable:4996)

typedef signed long int Long;

//�����
int main(int argc, char* argv[]);
Long Input();
Long GetBiggestNumber(Long number);
void Output(Long biggestNumber);

//���Ǻ�
int main(int argc, char* argv[]) {
	Long number;
	Long biggestNumber;
	//ȣ��
	number = Input();
	biggestNumber = GetBiggestNumber(number);
	Output(biggestNumber);

	return 0;
}
/*
�Լ���: Input
��  ��: ���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: ��
*/
Long Input() {
	Long number;
	scanf("%d", &number);
	return number;
}
/*
�Լ���: GetBiggestNumber
��  ��: �Է¹��� ���� �ڸ����� �������� ���� �� �ִ� ���� ū ���� ���Ͽ� ����Ѵ�.
��  ��: ��
��  ��: ���� ū ��
*/
Long GetBiggestNumber(Long number) {
	Long biggestNumber = 0;
	Long digit;
	Long count = 0;
	Long dividend;
	Long digitNumber;

	for (digit = 9; digit >= 0; digit--) {
		dividend = number;
		while (dividend > 0) {
			digitNumber = dividend % 10;
			if (digitNumber == digit) {
				count++;
			}
			dividend /= 10;
		}
		while (count > 0) {
			biggestNumber = biggestNumber * 10 + digit;
			count--;
		}
	}
	return biggestNumber;
}
/*
�Լ���: Output
��  ��: ���� ū ���� ����Ϳ� ����Ѵ�.
��  ��: ���� ū ��
��  ��: ����
*/
void Output(Long biggestNumber) {
	printf("���� ū �� : %d\n", biggestNumber);
}
