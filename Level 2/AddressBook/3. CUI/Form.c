#pragma once
//Form.c

#include "AddressBook.h"
#include "Form.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	AddressBook addressBook;
	int menu;

	Create(&addressBook, 1000);
	DisplayMenu();
	rewind(stdin); scanf("%d", &menu);
	while (menu != 0) {
		switch (menu) {
		case 1: FormForRecording(&addressBook); break;
		case 2: FormForFinding(&addressBook); break;
		case 3: FormForCorrecting(&addressBook); break;
		case 4: FormForErasing(&addressBook); break;
		case 5: FormForArranging(&addressBook); break;
		case 6: FormForView(&addressBook); break;
		default: break;
		}
		DisplayMenu();
		rewind(stdin); scanf("%d", &menu);
	}
	Destroy(&addressBook);

	return 0;
}
//DisplayMenu
void DisplayMenu() {
	int menu;
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t     �ּҷ� Version 0.05\n");
	printf("\t\t\t     =====================\n");
	printf("\t\t\t     [1] �����ϱ�\n");
	printf("\t\t\t     [2] ã    ��\n");
	printf("\t\t\t     [3] �� ġ ��\n");
	printf("\t\t\t     [4] �� �� ��\n");
	printf("\t\t\t     [5] �����ϱ�\n");
	printf("\t\t\t     [6] ��ü����\n");
	printf("\t\t\t     [0] �� �� ��\n");
	printf("\t\t\t     ---------------------\n");
	printf("\t\t\t     �޴��� �����Ͻʽÿ�! ");
}
//FormForRecording
void FormForRecording(AddressBook *addressBook) {
	char name[11];
	char address[64];
	char telephoneNumber[12];
	char emailAddress[64];
	char recording;
	char going = 'Y';
	Long index;

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n");
		printf("       �ּҷ� Version 0.05 - �����ϱ�\n");
		printf("       ===========================================================\n");
		printf("       ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("       ��      �� : "); rewind(stdin); gets(address);
		printf("       ��ȭ  ��ȣ : "); rewind(stdin); scanf("%s", telephoneNumber);
		printf("       �̸����ּ� : "); rewind(stdin); scanf("%s", emailAddress);
		printf("       -----------------------------------------------------------\n");
		printf("       �����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(addressBook, name, address, telephoneNumber, emailAddress);
			printf("       ===========================================================\n");
			printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
			printf("       -----------------------------------------------------------\n");
			printf("       %-4d %-10s %-20s %-11s %-10s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
		}
		printf("       ===========================================================\n");
		printf("       ����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); going = getchar();
	}
}
//FormForFinding
void FormForFinding(AddressBook *addressBook) {
	char name[11];
	Long(*indexes);
	Long count;
	char going = 'Y';
	Long index;
	Long i;

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n");
		printf("       �ּҷ� Version 0.05 - ã��\n");
		printf("       ===========================================================\n");
		printf("       ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("       ===========================================================\n");
		Find(addressBook, name, &indexes, &count);
		printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
		printf("       -----------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("       %-4d %-10s %-20s %-11s %-10s\n", i + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
			i++;
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("       ===========================================================\n");
		printf("       ����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); going = getchar();
	}
}
//FormForCorrecting
void FormForCorrecting(AddressBook *addressBook) {
	char name[11];
	Long(*indexes);
	Long count;
	Long index;
	char address[64];
	char telephoneNumber[12];
	char emailAddress[64];
	char correcting;
	char going = 'Y';
	Long i;

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n");
		printf("       �ּҷ� Version 0.05 - ��ġ��\n");
		printf("       ===========================================================\n");
		printf("       ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("       ===========================================================\n");
		Find(addressBook, name, &indexes, &count);
		printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
		printf("       -----------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("       %-4d %-10s %-20s %-11s %-10s\n", i + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
			i++;
		}
		if (count > 0) {
			printf("       ===========================================================\n");
			printf("       ��      ȣ : "); rewind(stdin); scanf("%d", &index);
			index = indexes[index - 1];
			printf("       ��      �� : %s ", addressBook->personals[index].address); rewind(stdin); gets(address);
			if (strcmp(address, "") == 0) {
				strcpy(address, addressBook->personals[index].address);
			}
			printf("       ��ȭ  ��ȣ : %s ", addressBook->personals[index].telephoneNumber); rewind(stdin); gets(telephoneNumber);
			if (strcmp(telephoneNumber, "") == 0) {
				strcpy(telephoneNumber, addressBook->personals[index].telephoneNumber);
			}
			printf("       �̸����ּ� : %s ", addressBook->personals[index].emailAddress); rewind(stdin); gets(emailAddress);
			if (strcmp(emailAddress, "") == 0) {
				strcpy(emailAddress, addressBook->personals[index].emailAddress);
			}
			printf("       ===========================================================\n");
			printf("       ��ġ�ðڽ��ϱ�? (Yes/No) "); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = Correct(addressBook, index, address, telephoneNumber, emailAddress);
				printf("       ===========================================================\n");
				printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
				printf("       -----------------------------------------------------------\n");
				printf("       %-4d %-10s %-20s %-11s %-10s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("       ===========================================================\n");
		printf("       ����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); going = getchar();
	}
}
//FormForErasing
void FormForErasing(AddressBook *addressBook) {
	char name[11];
	Long(*indexes);
	Long count;
	Long index;
	char erasing;
	char going = 'Y';
	Long i;

	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("       �ּҷ� Version 0.05 - �����\n");
		printf("       ===========================================================\n");
		printf("       ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("       ===========================================================\n");
		Find(addressBook, name, &indexes, &count);
		printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
		printf("       -----------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			index = indexes[i];
			printf("       %-4d %-10s %-20s %-11s %-10s\n", i + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
			i++;
		}
		if (count > 0) {
			printf("       ===========================================================\n");
			printf("       ��      ȣ : "); rewind(stdin); scanf("%d", &index);
			printf("       ===========================================================\n");
			printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
			printf("       -----------------------------------------------------------\n");
			index = indexes[index - 1];
			printf("       %-4d %-10s %-20s %-11s %-10s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address, addressBook->personals[index].telephoneNumber, addressBook->personals[index].emailAddress);
			printf("       ===========================================================\n");
			printf("       ����ðڽ��ϱ�? (Yes/No) "); rewind(stdin); erasing = getchar();
			if (erasing == 'Y' || erasing == 'y') {
				index = Erase(addressBook, index);
				if (index == -1) {
					printf("       ==========================================================\n");
					printf("       ���������ϴ�.\n");
				}
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("       ===========================================================\n");
		printf("       ����Ͻðڽ��ϱ�? (Yes/No) "); rewind(stdin); going = getchar();
	}
}
//FormForArranging
void FormForArranging(AddressBook *addressBook) {
	Long i = 0;
	Long j;

	Arrange(addressBook);
	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n\n");
		printf("       �ּҷ� Version 0.05 - �����ϱ�\n");
		printf("       ===========================================================\n");
		printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
		printf("       -----------------------------------------------------------\n");
		j = 1;
		while (i < addressBook->length && j <= 5) {
			printf("       %-4d %-10s %-20s %-11s %-10s\n", i + 1, addressBook->personals[i].name, addressBook->personals[i].address, addressBook->personals[i].telephoneNumber, addressBook->personals[i].emailAddress);
			i++;
			j++;
		}
		printf("       ===========================================================\n");
		printf("       �ƹ� Ű�� �������� "); rewind(stdin); getchar();
	}
}
//FormForView
void FormForView(AddressBook *addressBook) {
	Long i = 0;
	Long j;

	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n\n");
		printf("       �ּҷ� Version 0.05 - �����ϱ�\n");
		printf("       ===========================================================\n");
		printf("       ��ȣ ����       �ּ�                 ��ȭ��ȣ    �̸����ּ�\n");
		printf("       -----------------------------------------------------------\n");
		j = 1;
		while (i < addressBook->length && j <= 5) {
			printf("       %-4d %-10s %-20s %-11s %-10s\n", i + 1, addressBook->personals[i].name, addressBook->personals[i].address, addressBook->personals[i].telephoneNumber, addressBook->personals[i].emailAddress);
			i++;
			j++;
		}
		printf("       ===========================================================\n");
		printf("       �ƹ� Ű�� �������� "); rewind(stdin); getchar();
	}
}