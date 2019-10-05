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
	
	Destroy(&wordBook);

	return 0;
}
/*
�Լ���: Create
��  ��: ���� ���ܾ� �迭�� �Ҵ��Ѵ�.
��  ��: �Ҵ緮
��  ��: ����
*/
void Create(WordBook *wordBook, Long capacity) {
	wordBook->englishWords = (EnglishWord(*))calloc(capacity, sizeof(EnglishWord));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
/*
�Լ���: Record
��  ��: �ܾ��忡 �����Ѵ�.
��  ��: �ܾ�, ǰ��, ��, ����
��  ��: ��ġ
*/
Long Record(WordBook *wordBook, char(*word), char(*wordClass), char(*meaning), char(*example)) {
	Long index;
	EnglishWord(*englishWords);
	Long i;

	if (wordBook->length >= wordBook->capacity) {
		englishWords = (EnglishWord(*))calloc(wordBook->capacity + 1, sizeof(EnglishWord));
		i = 0;
		while (i < wordBook->length) {
			englishWords[i] = wordBook->englishWords[i];
			i++;
		}
		if (wordBook->englishWords != NULL) {
			free(wordBook->englishWords);
		}
		wordBook->englishWords = englishWords;
		(wordBook->capacity)++;
	}
	index = wordBook->length;
	strcpy(wordBook->englishWords[index].word, word);
	strcpy(wordBook->englishWords[index].wordClass, wordClass);
	strcpy(wordBook->englishWords[index].meaning, meaning);
	strcpy(wordBook->englishWords[index].example, example);
	(wordBook->length)++;

	return index;
}
/*
�Լ���: Find
��  ��: �ܾ��� �Է¹޾� �� ������ ã�´�.
��  ��: �ܾ�
��  ��: ��ġ��, ����
*/
void Find(WordBook *wordBook, char(*word), Long* (*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(wordBook->length, sizeof(Long));
	while (i < wordBook->length) {
		if (strcmp(wordBook->englishWords[i].word, word) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
/*
�Լ���: Correct
��  ��: ��ġ�� ���� ������ ��ģ��.
��  ��: ��ġ, ǰ��, ��, ����
��  ��: ��ġ
*/
Long Correct(WordBook *wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	strcpy(wordBook->englishWords[index].wordClass, wordClass);
	strcpy(wordBook->englishWords[index].meaning, meaning);
	strcpy(wordBook->englishWords[index].example, example);

	return index;
}
/*
�Լ���: Erase
��  ��: ��ġ�� ���� ������ �����.
��  ��: ��ġ
��  ��: ��ġ
*/
Long Erase(WordBook *wordBook, Long index) {
	EnglishWord(*englishWords);
	Long i = 0;
	Long j = 0;

	if (wordBook->capacity > 1) {
		englishWords = (EnglishWord(*))calloc(wordBook->capacity - 1, sizeof(EnglishWord));
	}
	while(i < wordBook->length){
		if (i != index) {
			englishWords[j] = wordBook->englishWords[i];
			j++;
		}
		i++;
	}
	if (wordBook->englishWords != NULL) {
		free(wordBook->englishWords);
		wordBook->englishWords = NULL;
	}
	if (wordBook->capacity > 1) {
		wordBook->englishWords = englishWords;
	}
	(wordBook->capacity)--;
	(wordBook->length)--;
	index = -1;

	return index;
}
/*
�Լ���: Arrange
��  ��: �ܾ����� ������������ �����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Arrange(WordBook *wordBook) {
	EnglishWord englishWord;
	Long i = 1;
	Long j;

	while (i < wordBook->length) {
		englishWord = wordBook->englishWords[i];
		j = i - 1;
		while (j >= 0 && strcmp(englishWord.word, wordBook->englishWords[j].word) < 0) {
			wordBook->englishWords[j + 1] = wordBook->englishWords[j];
			j--;
		}
		wordBook->englishWords[j + 1] = englishWord;
		i++;
	}
}
/*
�Լ���: Destroy
��  ��: �ܾ����� ���ش�.
��  ��: ����
��  ��: ����
*/
void Destroy(WordBook *wordBook) {
	if (wordBook->englishWords != NULL) {
		free(wordBook->englishWords);
	}
}