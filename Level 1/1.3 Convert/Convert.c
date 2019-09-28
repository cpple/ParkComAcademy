/*
���ϸ�: Convert.c
��  ��: �µ� ������ ��ġ�� �Է¹޾� ������ ȭ����, ȭ���� ������ ��ȯ�Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.19
*/
#include<stdio.h>
#pragma warning(disable:4996)

//�����
int main(int argc, char* argv[]);
void Input(char *unit, float *value);
void Convert(char unit, float value, char *convertUnit, float *convertValue);
void Output(char convertUnit, float convertValue);

//���Ǻ�
int main(int argc, char* argv[]) {
	char unit;
	float value;
	char convertUnit;
	float convertValue;
	//ȣ��
	Input(&unit, &value);
	Convert(unit, value, &convertUnit, &convertValue);
	Output(convertUnit, convertValue);

	return 0;
}
/*
�Լ���: Input
��  ��: �µ� ������ �µ� ��ġ�� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: �µ� ����, �µ� ��ġ
*/
void Input(char *unit, float *value) {
	scanf("%c %f", unit, value);
}
/*
�Լ���: Convert
��  ��: ������ ȭ����, ȭ���� ������ ��ȯ�Ͽ� ����Ѵ�.
��  ��: �µ� ����, �µ� ��ġ
��  ��: ��ȯ �µ� ����, ��ȯ �µ� ��ġ
*/
void Convert(char unit, float value, char *convertUnit, float *convertValue) {
	if (unit == 'C' || unit == 'c') {
		*convertUnit = 'F';
		*convertValue = value * 1.8F + 32.0F;
	}
	else if (unit == 'F' || unit == 'f') {
		*convertUnit = 'C';
		*convertValue = (value - 32.0F) / 1.8F;
	}
	else {
		*convertUnit = 'E';
		*convertValue = 0.0F;
	}
}
/*
�Լ���: Output
��  ��: ��ȯ�� �µ� ������ ��ġ�� ����Ϳ� ����Ѵ�.
��  ��: ��ȯ �µ� ����, ��ȯ �µ� ��ġ
��  ��: ����
*/
void Output(char convertUnit, float convertValue) {
	if (convertUnit!='E') {
		printf("��ȯ ���: %.1f %c\n", convertValue, convertUnit);
	}
	else {
		printf("ERROR DATA = %.1f\n", convertValue);
	}
}