/*
���� ��Ī: Escape.c
���: �칰�� ���̸� �Է¹޾� �� �칰�� �����̰� Ż���ϴ� �� �ɸ��� �ϼ��� ���Ѵ�.
�ۼ���: ������
�ۼ�����: 19.01.16
*/
#include<stdio.h>
#define UP 3
#define DOWN 2

//�ڷ��� ����
typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
ULong Input();
ULong Escape(ULong wellHeight);
void Output(ULong wellHeight, ULong day);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong wellHeight;
	ULong day;

	//�Լ� ȣ��
	wellHeight = Input();
	day = Escape(wellHeight);
	Output(wellHeight, day);

	return 0;
}
/*
�Լ� ��Ī: Input
���: �칰�� ���̸� �Է¹޴´�.
�Է�: ����
���: �칰�� ����
*/
ULong Input() {
	ULong wellHeight;
	scanf("%d", &wellHeight);
	return wellHeight;
}
/*
�Լ� ��Ī: Escape
���: �칰�� ���̸� �Է¹޾� �����̰� �� �칰�� Ż���ϴµ� �ɸ��� �ϼ��� ���Ͽ� ����Ѵ�.
�Է�: �칰�� ����
���: �ϼ�
*/
ULong Escape(ULong wellHeight) {
	ULong day = 1;
	ULong upHeight = UP;
	ULong downHeight;

	while (upHeight < wellHeight) {
		downHeight = upHeight - DOWN;
		day++;
		upHeight = downHeight + UP;
	}
	return day;
}
/*
�Լ� ��Ī: Output
���: �����̰� �칰�� Ż���� �� �ɸ� �ϼ��� ����Ϳ� ����Ѵ�.
�Է�: �칰�� ����, �ϼ�
���: ����
*/
void Output(ULong wellHeight, ULong day) {
	printf("%dm�� �칰�� %d�� �� Ż���ߴ�.\n", wellHeight, day);
}