#pragma once
#include "Form.h"
#include "WordBook.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	WordBook wordBook;
	int menu;

	Create(&wordBook, 1000);
	DisplayMenu();
	rewind(stdin); scanf("%d", &menu);
	while (menu != 0) {
		switch (menu) {
		case 1: FormForRecording(&wordBook); break;
		case 2: FormForFinding(&wordBook); break;
		case 3: FormForCorrecting(&wordBook); break;
		case 4: FormForErasing(&wordBook); break;
		case 5: FormForArranging(&wordBook); break;
		case 6: FormForView(&wordBook); break;
		default: break;
		}
		DisplayMenu();
		rewind(stdin); scanf("%d", &menu);
	}
	Destroy(&wordBook);

	return 0;
}
void DisplayMenu() {
	system("cls");
	printf("\n");
	printf("   �ܾ��� ver. 0.05\n");
	printf("   =========================================================================\n");
	printf("   [1] �����ϱ�\n");
	printf("   [2] ã    ��\n");
	printf("   [3] �� ġ ��\n");
	printf("   [4] �� �� ��\n");
	printf("   [5] �����ϱ�\n");
	printf("   [6] ��ü����\n");
	printf("   [0] �� �� ��\n");
	printf("   -------------------------------------------------------------------------\n");
	printf("   �޴��� �����Ͻʽÿ�! ");
}
void FormForRecording(WordBook *wordBook) {
	char word[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
	Long index;
	char recording;
	char going = 'Y';

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - �����ϱ�\n");
		printf("   ============================================================================\n");
		printf("   �ܾ� : "); rewind(stdin); scanf("%s", word);
		printf("   ǰ�� : "); rewind(stdin); scanf("%s", wordClass);
		printf("   �ǹ� : "); rewind(stdin); scanf("%s", meaning);
		printf("   ���� : "); rewind(stdin); gets(example);
		printf("   ============================================================================\n");
		printf("   �����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(wordBook, word, wordClass, meaning, example);
			printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
			printf("   ----------------------------------------------------------------------------\n");
			printf("   %-4d %-10s %-16s %-32s %-32s\n", index + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
		}
		printf("   ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); going = getchar();
	}
}
void FormForFinding(WordBook *wordBook) {
	char word[64];
	char going = 'Y';
	Long i;
	Long index;
	Long(*indexes);
	Long count;

	while (going== 'Y' || going == 'y') {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - ã��\n");
		printf("   ============================================================================\n");
		printf("   �ܾ� : "); rewind(stdin); scanf("%s", word);
		printf("   ============================================================================\n");
		Find(wordBook, word, &indexes, &count);
		printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
		printf("   ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("   %-4d %-10s %-16s %-32s %-32s\n", i + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
			i++;
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
	}
}
void FormForCorrecting(WordBook *wordBook) {
	char word[64];
	Long i;
	Long index;
	Long(*indexes);
	Long count;
	char wordClass[11];
	char meaning[64];
	char example[128];
	char correcting;
	char going = 'Y';

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - ��ġ��\n");
		printf("   ============================================================================\n");
		printf("   �ܾ� : "); rewind(stdin); scanf("%s", word);
		printf("   ============================================================================\n");
		Find(wordBook, word, &indexes, &count);
		printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
		printf("   ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("   %-4d %-10s %-16s %-32s %-32s\n", i + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
			i++;
		}
		if (count > 0) {
			printf("   ============================================================================\n");
			printf("   ��ȣ : "); rewind(stdin); scanf("%d", &index);
			index = indexes[index - 1];
			printf("   ǰ�� : %s ", wordBook->englishWords[index].wordClass); rewind(stdin); gets(wordClass);
			if (strcmp(wordClass, "") == 0) {
				strcpy(wordClass, wordBook->englishWords[index].wordClass);
			}
			printf("   �ǹ� : %s ", wordBook->englishWords[index].meaning); rewind(stdin); gets(meaning);
			if (strcmp(meaning, "") == 0) {
				strcpy(meaning, wordBook->englishWords[index].meaning);
			}
			printf("   ���� : %s ", wordBook->englishWords[index].example); rewind(stdin); gets(example);
			if (strcmp(example, "") == 0) {
				strcpy(example, wordBook->englishWords[index].example);
			}
			printf("   ============================================================================\n");
			printf("   ��ġ�ڽ��ϱ�?(Yes/No) "); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = Correct(wordBook, index, wordClass, meaning, example);
				printf("   ============================================================================\n");
				printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
				printf("   ----------------------------------------------------------------------------\n");
				printf("   %-4d %-10s %-16s %-32s %-32s\n", index + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
	}
}
void FormForErasing(WordBook *wordBook){
	char word[64];
	Long index;
	Long(*indexes);
	Long count;
	char erasing;
	char going = 'Y';
	Long i;

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - �����\n");
		printf("   ============================================================================\n");
		printf("   �ܾ� : "); rewind(stdin); scanf("%s", word);
		printf("   ============================================================================\n");
		Find(wordBook, word, &indexes, &count);
		printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
		printf("   ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("   %-4d %-10s %-16s %-32s %-32s\n", i + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
			i++;
		}
		if (count > 0) {
			printf("   ============================================================================\n");
			printf("   ��ȣ : "); rewind(stdin); scanf("%d", &index);
			printf("   ============================================================================\n");
			printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
			printf("   ----------------------------------------------------------------------------\n");
			printf("   %-4d %-10s %-16s %-32s %-32s\n", index + 1, wordBook->englishWords[index].word, wordBook->englishWords[index].wordClass, wordBook->englishWords[index].meaning, wordBook->englishWords[index].example);
			printf("   ============================================================================\n");
			printf("   ����ðڽ��ϱ�?(Yes/No) "); rewind(stdin); erasing = getchar();
			if (erasing == 'Y' || erasing == 'y') {
				index = Erase(wordBook, index);
				if (index == -1) {
					printf("   ============================================================================\n");
					printf("   ���������ϴ�.\n");
				}
			}

		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(Yes/No) "); rewind(stdin); going = getchar();
	}
}
void FormForArranging(WordBook *wordBook) {
	Long i = 0;
	Long j;

	Arrange(wordBook);
	while (i < wordBook->length) {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - �����ϱ�\n");
		printf("   ============================================================================\n");
		printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
		printf("   ----------------------------------------------------------------------------\n");
		j = 1;
		while (i < wordBook->length && j <= 5) {
			printf("   %-4d %-10s %-16s %-32s %-32s\n", i + 1, wordBook->englishWords[i].word, wordBook->englishWords[i].wordClass, wordBook->englishWords[i].meaning, wordBook->englishWords[i].example);
			i++;
			j++;
		}
		printf("   ============================================================================\n");
		printf("   �ƹ� Ű�� �������� "); rewind(stdin); getchar();
	}
}
void FormForView(WordBook *wordBook) {
	Long i = 0;
	Long j;

	while (i < wordBook->length) {
		system("cls");
		printf("\n");
		printf("   �ܾ��� ver. 0.05 - ��ü����\n");
		printf("   ============================================================================\n");
		printf("   ��ȣ �ܾ�       ǰ��       �ǹ�             ����                            \n");
		printf("   ----------------------------------------------------------------------------\n");
		j = 1;
		while (i < wordBook->length && j <= 5) {
			printf("   %-4d %-10s %-16s %-32s %-32s\n", i + 1, wordBook->englishWords[i].word, wordBook->englishWords[i].wordClass, wordBook->englishWords[i].meaning, wordBook->englishWords[i].example);
			i++;
			j++;
		}
		printf("   ============================================================================\n");
		printf("   �ƹ� Ű�� �������� "); rewind(stdin); getchar();
	}
}