/*
���� ��Ī: IsPerfectNumber.c
���: ���� �Է¹޾� ���������� �Ǻ��ϴ�.
�ۼ���: ������
�ۼ�����: 19.01.16.
*/
#include<stdio.h>
typedef enum _boolean {FALSE=0, TRUE=1} Boolean;
typedef unsigned long int ULong;
//�����
int main(int argc, char* argv[]);
ULong Input();
Boolean IsPerfectNumber(ULong number);
void Output(ULong numeber, Boolean IsPerfectNumber);
//���Ǻ�
int main(int argc, char* argv[]) {
	ULong number;
	Boolean isPerfectNumber;
	//�Լ� ȣ��
	number = Input();
	isPerfectNumber = IsPerfectNumber(number);
	Output(number, isPerfectNumber);

	return 0;
}
/*
�Լ� ��Ī: Input
���: ���� �Է¹޴´�.
�Է�: ����
���: ��
*/
ULong Input() {
	ULong number;
	scanf("%d", &number);
	return number;
}
/*
�Լ� ��Ī: IsPerfectNumber
���: ���� ���������θ� �Ǻ��Ѵ�.
�Է�: ��
���: ����������
*/
Boolean IsPerfectNumber(ULong number) {
	Boolean isPerfectNumber;
	ULong factor = 0;
	ULong sum = 0;
	ULong i = 1;
	ULong remainder;

	while (i < number) {
		factor++;
		remainder = number % factor;
		if (remainder == 0) {
			sum += factor;
		}
		i++;
	}
	if (sum == number) {
		isPerfectNumber = TRUE;
	}
	else {
		isPerfectNumber = FALSE;
	}
	return isPerfectNumber;
}
/*
�Լ� ��Ī: Output
���: �������� �Ǻ��� ����� ����Ϳ� ����Ѵ�.
�Է�: ��, ����������
���: ����
*/
void Output(ULong number, Boolean isPerfectNumber) {
	if (isPerfectNumber == TRUE) {
		printf("%d�� �������Դϴ�.\n", number);
	}
	else {
		printf("%d�� �������� �ƴմϴ�.\n", number);
	}
}
