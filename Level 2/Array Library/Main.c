#include "Array.h"
#include <stdio.h> //printf
#include <stdlib.h> //free

int Compare(void* one, void* other);

int main(int argc, char* argv[]) {
	Array array;
	Long index; //Long ��ȯ �Լ��� ���
	Long object; //�Է�
	Long key; //�Է�
	Long(*indexes); //~SearchDuplicate ���
	Long count; //~SearchDuplicate ���
	Array one;
	Array other;
	Long ret; //GetAt ���
	Long i; //�ݺ������

	//1. �迭�� 3��ŭ �Ҵ��ϴ�.
	Create(&array, 3, sizeof(Long));

	//2. ���� 30�� ��ġ 1�� �����ϴ�.
	object = 30;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30
	
	//3. ���� 10�� ��ġ 2�� �����ϴ�.
	object = 10;
	index = Store(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 10

	//4. ���� 20�� ��ġ 3�� �����ϴ�.
	object = 20;
	index = Store(&array, 2, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 10 20

	//5. ���� 20�� ��ġ 2�� �����ϴ�.
	object = 20;
	index = Insert(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//30 20 10 20

	//6. 20�� �����˻��ϴ�.
	key = 20;
	LinearSearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}
	
	//7. �� ���� �迭��Ҹ� �����ϴ�.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�.\n");
	}												//30 20 10

	//8. �� �տ� ���� 50�� �߰��ϴ�.
	object = 50;
	index = AppendFromFront(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 30 20 10

	//9. 10�� �����˻��ϴ�.
	key = 10;
	index = LinearSearchUnique(&array, &key, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//10. ��ǰ �����ϴ�.
	BubbleSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//10 20 30 50

	//11. Ŭ�����ϴ�.
	Clear(&array);
	if (array.front == NULL) {
		printf("Ŭ�����߽��ϴ�.\n");
	}

	//12. one �迭�� 2��ŭ �����ϴ�.
	Create(&one, 2, sizeof(Long));

	//13. ���� 50�� one�� ��ġ 1�� �����ϴ�.
	object = 50;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50

	//14. ���� 90�� one�� ��ġ 2�� �����ϴ�.
	object = 90;
	index = Store(&one, 1, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 90

	//15. other �迭�� 3��ŭ �����ϴ�.
	Create(&other, 3, sizeof(Long));

	//16. ���� 60�� other�� ��ġ 1�� �����ϴ�.
	object = 60;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60

	//17. ���� 70�� other�� ��ġ 2�� �����ϴ�.
	object = 70;
	index = Store(&other, 1, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60 70

	//18. ���� 80�� other�� ��ġ 3�� �����ϴ�.
	object = 80;
	index = Store(&other, 2, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//60 70 80

	//19. one�� other�� �����ϴ�.
	Merge(&array, one, other, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//50 60 70 80 90 

	//20. ��ġ 4�� �迭��Ҹ� �����ϴ�.
	index = Delete(&array, 3, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�.\n");					//50 60 70 90
	}

	//21. 70�� �̺а˻��ϴ�.
	key = 70;
	index = BinerySearchUnique(&array, &key, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//22. �� �ڿ� ���� 40�� �߰��ϴ�.
	object = 40;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//50 60 70 90 40

	//23. ���� �����ϴ�.
	SelectionSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {	
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//40 50 60 70 90

	//24. �� ���� �迭��Ҹ� �����ϴ�.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�.\n");
	}												//50 60 70 90
	
	//25. ��ġ 1�� �迭��Ҹ� ���� 90���� �����ϴ�.
	object = 90;
	index = Modify(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);							//90 60 70 90

	//26. ���� �����ϴ�.
	InsertionSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");									//60 70 90 90

	//27. 90�� �̺� �˻��ϴ�.
	key = 90;
	BinerySearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}

	//28. other�� ���ִ�.
	Destroy(&other);

	//29. one�� ���ִ�.
	Destroy(&one);

	//30. �迭�� ���ִ�.
	Destroy(&array);

	return 0;
}
int Compare(void* one, void* other) {
	Long *one_ = (Long*)one;
	Long *other_ = (Long*)other;
	int ret;

	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_ < *other_) {
		ret = -1;
	}

	return ret;
}