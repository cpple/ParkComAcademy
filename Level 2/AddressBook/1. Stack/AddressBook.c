//AddressBook.c
/*
���ϸ�: AddressBook.c
��  ��: �����ϰ� ã�� ��ġ�� ����� ������ �� �ִ� �ּҷ� ���α׷�
�ۼ���: ������
�ۼ���: 19.2.1.
*/
#include"AddressBook.h"
#include<stdio.h>
#include<string.h>
#pragma warning(disable: 28719)
int main(int argc, char* argv[]) {
	AddressBook addressBook = { {{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""}},MAX,0 };
	Long indexes[MAX];
	Long count;
	Long index;
	Long i;
	//ȣ��
	//1. �����ϴ�
	index = Record(&addressBook, "ȫ�浿", "�����", "0101111", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "��浿", "������", "0102222", "ko@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "���浿", "�뱸��", "0103333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "ȫ�浿", "�λ��", "0104444", "hongd@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//2. ã��
	Find(&addressBook, "ȫ�浿", indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
		i++;
	}
	printf("\n");
	//3. ��ġ��
	index = Correct(&addressBook, 2, "���ֵ�", "0103333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//4. �����
	index = Erase(&addressBook, 1);
	if (index == -1) {
		printf("��������!\n");
	}
	printf("\n");
	//5. �����ϴ�
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].telephoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	return 0;
}
/*
�Լ���: Record
��  ��: �ּҷϿ� ����, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �����Ѵ�.
��  ��: ����, �ּ�, ��ȭ��ȣ, �̸����ּ�
��  ��: ��ġ
*/
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress)) {
	Long index = -1;
	Long i = 0;
	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0) {
		i++;
	}
	if (i < addressBook->capacity) {
		index = i;
		strcpy(addressBook->personals[index].name, name);
		strcpy(addressBook->personals[index].address, address);
		strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
		strcpy(addressBook->personals[index].emailAddress, emailAddress);
		(addressBook->length)++;
	}
	return index;
}
/*
�Լ���: Find
��  ��: ������ �Է¹޾� �� ��ġ�� ã�´�.
��  ��: ����
��  ��: ��ġ��, ����
*/
void Find(AddressBook *addressBook, char(*name), Long(*indexes), Long *count) {
	Long i = 0;
	Long j = 0;
	*count = 0;
	while (i < addressBook->length) {
		if (strcmp(addressBook->personals[i].name, name) == 0) {
			indexes[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}
/*
�Լ���: Correct
��  ��: � ��ġ�� �ּ�, ��ȭ��ȣ, �̸����ּҸ� ��ģ��.
��  ��: ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּ�
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
��  ��: � ��ġ�� ������ �����.
��  ��: ��ġ
��  ��; ��ġ
*/
Long Erase(AddressBook *addressBook, Long index) {
	strcpy(addressBook->personals[index].name, "X");
	index = -1;

	return index;
}
/*
�Լ���: Arrange
��  ��: �����Ѵ�.
��  ��: ����
��  ��: ����
*/
void Arrange(AddressBook *addressBook) {
	Personal personal;
	Long i = 0;
	Long j;
	while (i < (addressBook->length) - 1) {
		j = i + 1;
		while (j < addressBook->length) {
			if (strcmp(addressBook->personals[i].name, addressBook->personals[j].name) < 0) {
				personal = addressBook->personals[i];
				addressBook->personals[i] = addressBook->personals[j];
				addressBook->personals[j] = personal;
			}
			j++;
		}
		i++;
	}
	i = (addressBook->length) - 1;
	while (i >= 0 && strcmp(addressBook->personals[i].name, "X") == 0) {
		i--; 
	}
	j = 0;
	while (j < i) {
		personal = addressBook->personals[j];
		addressBook->personals[j] = addressBook->personals[i];
		addressBook->personals[i] = personal;
		i--;
		j++;
	}
}