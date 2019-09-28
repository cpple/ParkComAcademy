/*
���ϸ�: CompareHeights
��  ��: Ű���� �Է¹޾� ���� ū Ű�� �ι�°�� ū Ű�� ���Ͽ� ����Ѵ�.
�ۼ���: ������
�ۼ���: 19.1.23
*/
#include<stdio.h>
#define MAX 7
#pragma warning(disable:4996)

typedef unsigned long int ULong;

//�����
int main(int argc, char* argv[]);
void Input(ULong(*heights));
void CompareHeights(ULong(*heights), ULong *first, ULong *second);
void Output(ULong first, ULong second);

//���Ǻ�
int main(int argc, char* argv[]) {
	ULong heights[MAX];
	ULong first;
	ULong second;
	//ȣ��
	Input(heights);
	CompareHeights(heights, &first, &second);
	Output(first, second);

	return 0;
}
/*
�Լ���: Input
��  ��: Ű���� �ܺ��Է¹޴´�.
��  ��: ����
��  ��: Ű��
*/
void Input(ULong(*heights)) {
	ULong i;
	for (i = 0; i < MAX; i++) {
		scanf("%d", heights + i);
	}
}
/*
�Լ���: CompareHeights
��  ��: Ű�� �� ���� ū Ű�� �ι�°�� ū Ű�� ���Ͽ� ����Ѵ�.
��  ��: Ű��
��  ��: ����ūŰ, �ι�°ūŰ
*/
void CompareHeights(ULong(*heights), ULong *first, ULong *second) {
	ULong i;
	*first = 0;

	for (i = 0; i < MAX; i++) {
		if (heights[i] > *first) {
			*second = *first;
			*first = heights[i];
		}
		else if (heights[i] > *second) {
			*second = heights[i];
		}
	}
}
/*
�Լ���: Output
��  ��: ���� ū Ű�� �ι�°�� ū Ű�� ����Ϳ� ����Ѵ�.
��  ��: ����ūŰ, �ι�°ūŰ
��  ��: ����
*/
void Output(ULong first, ULong second) {
	printf("���� ū Ű: %d\n�ι�° ū Ű: %d\n", first, second);
}