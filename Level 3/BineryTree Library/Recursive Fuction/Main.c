#include "BineryTree.h"
#include <stdio.h>

int CompareKeys(void *one, void *other);

int main(int argc, char* argv[]) {
	BineryTree bineryTree;
	BineryNode *node;
	Long key;
	Long ret;

	//1. �̺а˻�Ʈ���� �����.
	Create(&bineryTree);
	//2. 100�� �����Ѵ�.
	key = 100;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//3. 50�� �����Ѵ�.
	key = 50;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. 200�� �����Ѵ�.
	key = 200;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. 50�� ã�´�.
	key = 50;
	node = Search(&bineryTree, &key, CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. 50�� �����Ѵ�.
	node = Delete(&bineryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("���������ϴ�.\n");
	}
	//7. 150�� �����Ѵ�.
	key = 150;
	node = Insert(&bineryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&bineryTree, node, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. ������ �����.
	MakeBalance(&bineryTree, sizeof(Long));
	//9. �̺а˻�Ʈ���� ���ش�.
	Destroy(&bineryTree);

	return 0;
}
int CompareKeys(void *one, void *other) {
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