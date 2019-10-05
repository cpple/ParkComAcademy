/*
���ϸ�: AddressBook.c
��  ��: �����ϰ� ã�� ��ġ�� ����� ������ �� �ִ� �ּҷ� ���α׷�
�ۼ���: ������
�ۼ���: 19.2.5.
*/
#include "AddressBook.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//�Լ� ����
int main(int argc, char* argv[]) {
	AddressBook addressBook;
	Long (*indexes);
	Long count;
	Long index;
	Long i;

	//ȣ��
	
	//1. �����ϴ�
	Create(&addressBook, 3);
	
	//2. �����ϴ�
	index = Record(&addressBook, "ȫ�浿", "�����", "01011111111", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "��浿", "������", "01022222222", "ko@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "���浿", "�뱸��", "01033333333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "ȫ�浿", "�λ��", "01044444444", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//3. ã��
	Find(&addressBook, "ȫ�浿", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");
	//4. ��ġ��
	index = Correct(&addressBook, 2, "���ֽ�", "01033333333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//5. �����
	index = Erase(&addressBook, 1);
	if (index == -1) {
		printf("��������!\n");
	}
	printf("\n");
	//6. �����ϴ�
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].telephoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	printf("\n");
	//7. ���ִ�
	Destroy(&addressBook);


	return 0;
}
/*
�Լ���: Create
��  ��: �ּҷ��� �����.
��  ��: �Ҵ緮
��  ��: ����
*/
void Create(AddressBook *addressBook, Long capacity) {
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}
/*
�Լ���: Record
��  ��: �ּҷϿ� ������ �����ϴ�.
��  ��: ����, �ּ�, ��ȭ��ȣ, �̸���
��  ��: ��ġ
*/
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
	Long index;
	Long i;
	Personal (*personals);

	if (addressBook->length >= addressBook->capacity) {
		personals = (Personal(*))calloc((addressBook->capacity)+1, sizeof(Personal));
		i = 0;
		while (i < addressBook->length) {
			personals[i] = addressBook->personals[i];
			i++;
		}
		if (addressBook->personals != NULL) {
			free(addressBook->personals);
		}
		addressBook->personals = personals;
		(addressBook->capacity)++;
	}
	index = addressBook->length;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	(addressBook->length)++;

	return index;
}
/*
�Լ���: Find
��  ��: ������ �Է¹޾� �� ������ ��ġ�� ã�´�.
��  ��: ����
��  ��: ��ġ��, ����
*/
void Find(AddressBook *addressBook, char(*name), Long* (*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count=0;

	*indexes = (Long(*))calloc(addressBook->length, sizeof(Long));
	while (i < addressBook->length) {
		if (strcmp(addressBook->personals[i].name, name) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
/*
�Լ���: Correct
��  ��: �Է¹��� ��ġ�� �ּҷ� ������ ��ġ��.
��  ��: ��ġ, �ּ�, ��ȭ��ȣ, �̸���
��  ��: ��ġ
*/
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);

	return index;
}
/*
�Լ���: Erase
��  ��: �Է¹��� ��ġ�� ������ �����.
��  ��: ��ġ
��  ��: ��ġ
*/
Long Erase(AddressBook *addressBook, Long index) {
	Personal(*personals);
	Long i = 0;
	Long j = 0;

	if (addressBook->capacity > 1) {
		personals = (Personal(*))calloc((addressBook->capacity) - 1, sizeof(Personal));
	}
	while (i < addressBook->length) {
		if (i != index) {
			personals[j] = addressBook->personals[i];
			j++;
		}
		i++;
	}
	if (addressBook->personals != NULL) {
		free(addressBook->personals);
		addressBook->personals = NULL;
	}
	if (addressBook->capacity > 1) {
		addressBook->personals = personals;
	}
	(addressBook->length)--;
	(addressBook->capacity)--;
	index = -1;

	return index;
}
/*
�Լ���: Arrange
��  ��: �ּҷ��� �����ϴ�.
��  ��: ����
��  ��: ����
*/
void Arrange(AddressBook *addressBook) {
	Long i = 0;
	Long j;
	Personal personals;

	while (i < (addressBook->length) - 1) {
		j = i + 1;
		while (j < addressBook->length) {
			if (strcmp(addressBook->personals[i].name, addressBook->personals[j].name) > 0) {
				personals = addressBook->personals[i];
				addressBook->personals[i] = addressBook->personals[j];
				addressBook->personals[j] = personals;
			}
			j++;
		}
		i++;
	}
}
/*
�Լ���: Destroy
��  ��: �ּҷ��� ���ش�.
��  ��: ����
��  ��: ����
*/
void Destroy(AddressBook *addressBook) {
	if (addressBook->personals != NULL) {
		free(addressBook->personals);
	}
}