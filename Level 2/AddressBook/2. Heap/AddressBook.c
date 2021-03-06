/*
파일명: AddressBook.c
기  능: 기재하고 찾고 고치고 지우고 정리할 수 있는 주소록 프로그램
작성자: 김찬형
작성일: 19.2.5.
*/
#include "AddressBook.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


//함수 정의
int main(int argc, char* argv[]) {
	AddressBook addressBook;
	Long (*indexes);
	Long count;
	Long index;
	Long i;

	//호출
	
	//1. 생성하다
	Create(&addressBook, 3);
	
	//2. 기재하다
	index = Record(&addressBook, "홍길동", "서울시", "01011111111", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "고길동", "대전시", "01022222222", "ko@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "정길동", "대구시", "01033333333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "홍길동", "부산시", "01044444444", "hong@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//3. 찾다
	Find(&addressBook, "홍길동", &indexes, &count);
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
	//4. 고치다
	index = Correct(&addressBook, 2, "제주시", "01033333333", "jung@");
	printf("%s\t%s\t%s\t%s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);
	printf("\n");
	//5. 지우다
	index = Erase(&addressBook, 1);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");
	//6. 정리하다
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		printf("%s\t%s\t%s\t%s\n", addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].telephoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	printf("\n");
	//7. 없애다
	Destroy(&addressBook);


	return 0;
}
/*
함수명: Create
기  능: 주소록을 만들다.
입  력: 할당량
출  력: 없음
*/
void Create(AddressBook *addressBook, Long capacity) {
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}
/*
함수명: Record
기  능: 주소록에 정보를 기재하다.
입  력: 성명, 주소, 전화번호, 이메일
출  력: 위치
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
함수명: Find
기  능: 성명을 입력받아 그 성명의 위치를 찾는다.
입  력: 성명
출  력: 위치들, 개수
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
함수명: Correct
기  능: 입력받은 위치의 주소록 정보를 고치다.
입  력: 위치, 주소, 전화번호, 이메일
출  력: 위치
*/
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress)) {
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);

	return index;
}
/*
함수명: Erase
기  능: 입력받은 위치의 정보를 지운다.
입  력: 위치
출  력: 위치
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
함수명: Arrange
기  능: 주소록을 정리하다.
입  력: 없음
출  력: 없음
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
함수명: Destroy
기  능: 주소록을 없앤다.
입  력: 없음
출  력: 없음
*/
void Destroy(AddressBook *addressBook) {
	if (addressBook->personals != NULL) {
		free(addressBook->personals);
	}
}