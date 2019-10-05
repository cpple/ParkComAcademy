/*
���ϸ�: WordBook.c
��  ��: �����ϰ� ã�� ��ġ�� ����� ������ �� �ִ� �ܾ��� ���α׷�
�ۼ���: ������
�ۼ���: 19.2.8.
*/
#include "WordBook.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//���Ǻ�

int main(int argc, char* argv[]) {
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i;

	//�׽�Ʈ �ó�����
	Create(&wordBook, 3);
	/*
	index = Record(&wordBook, "eat", "����", "�Դ�", "I eat banana.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "apple", "���", "���", "I like apple");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "pretty", "�����", "����", "You are pretty.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "where", "���ӻ�", "���", "Where are you going?");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	index = Record(&wordBook, "pretty", "�λ�", "��", "This shirt is pretty nice.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	printf("\n");

	Find(&wordBook, "pretty", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");

	index = Correct(&wordBook, 2, "�λ�", "��", "This shirt is pretty nice.");
	printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
	printf("\n");

	index = Erase(&wordBook, 4);
	if (index == -1) {
		printf("��������!\n");
	}
	printf("\n");

	Arrange(&wordBook);
	i = 0;
	while (i < wordBook.length) {
		index = i;
		printf("%s\t%s\t%s\t%s\n", wordBook.englishWords[index].word, wordBook.englishWords[index].wordClass, wordBook.englishWords[index].meaning, wordBook.englishWords[index].example);
		i++;
	}
	printf("\n");
	*/
	Destroy(&wordBook);

	return 0;
}

