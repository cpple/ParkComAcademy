#include "BusinessCardHolder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

/*
int main(int argc, char* argv[]) {
	BusinessCardHolder businessCardHolder;
	BusinessCard businessCard1 = { {"ȫ��", "����� ������", "021111", "021110", "hong.com"}, {"ȫ�浿", "0101111", "hong@", "���"}, NULL };
	BusinessCard businessCard2 = { {"����", "������ ������", "0432222", "0432220", "ko.com"}, {"��浿", "0102222", "ko@", "����"}, NULL };
	BusinessCard businessCard3 = { {"ȫ��", "�뱸�� �޼���", "0523333", "0523330", "hongB.com"}, {"ȫ�浿", "0103333", "gil@", "����"}, NULL };
	BusinessCard businessCard4 = { {"����", "�λ�� ������", "0514444", "0514440", "jung.com"}, {"���浿", "0104444", "jung@", "�븮"}, NULL };
	BusinessCard *index;
	BusinessCard* (*indexes);
	Long count;
	Long i;
	BusinessCard businessCard;
	BusinessCard *previous = NULL;

	//1. ����ø�� �����.
	Create(&businessCardHolder);

	//2. ����1�� �ȴ�.
	index = PutIn(&businessCardHolder, businessCard1);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);

	//3. ����2�� �ȴ�.
	index = PutIn(&businessCardHolder, businessCard2);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);

	//4. ����3�� �ȴ�.
	index = PutIn(&businessCardHolder, businessCard3);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);

	//5. ����4�� �ȴ�.
	index = PutIn(&businessCardHolder, businessCard4);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//6. ù ��° ������ ã��.
	index = First(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//7. ���� ������ ã��.
	index = Next(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//8. ������ ����.
	businessCard = PutOut(&businessCardHolder, index);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", businessCard.company.name, businessCard.company.address, businessCard.company.telephoneNumber, businessCard.company.faxNumber, businessCard.company.url,
		businessCard.personal.name, businessCard.personal.telephoneNumber, businessCard.personal.emailAddress, businessCard.personal.position);
	
	//9. ������ �ȴ�.
	index = PutIn(&businessCardHolder, businessCard);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//10. ȫ�浿�� ���Ե��� ã��.
	Find(&businessCardHolder, "ȫ�浿", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
			index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	
	//11. ������ ������ ã��.
	index = Last(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//12. ���� ������ ã��.
	index = Previous(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
		index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
	
	//13. ����ø�� �����ϴ�.
	Arrange(&businessCardHolder);
	index = First(&businessCardHolder);
	while (index != previous) {
		printf("%s\t%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.telephoneNumber, index->company.faxNumber, index->company.url,
			index->personal.name, index->personal.telephoneNumber, index->personal.emailAddress, index->personal.position);
		previous = index;
		index = Next(&businessCardHolder);
	}
	
	//14. ����ø�� ���ִ�.
	Destroy(&businessCardHolder);

	return 0;
}
*/
void Create(BusinessCardHolder *businessCardHolder) {
	businessCardHolder->first = NULL;
	businessCardHolder->length = 0;
	businessCardHolder->current = NULL;
}
BusinessCard* PutIn(BusinessCardHolder *businessCardHolder, BusinessCard businessCard) {
	BusinessCard *previous = NULL;

	businessCardHolder->current = businessCardHolder->first;
	while(businessCardHolder->current != NULL) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	businessCardHolder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
	*businessCardHolder->current = businessCard;
	if (previous != NULL) {
		previous->next = businessCardHolder->current;
	}
	else {
		businessCardHolder->first = businessCardHolder->current;
	}
	businessCardHolder->length++;

	return businessCardHolder->current;
}
void Find(BusinessCardHolder *businessCardHolder, char(*name), BusinessCard** (*indexes), Long *count) {
	Long i = 0;
	*count = 0;

	*indexes = (BusinessCard*(*))calloc(businessCardHolder->length, sizeof(BusinessCard*));
	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		if (strcmp(businessCardHolder->current->personal.name, name) == 0) {
			(*indexes)[i] = businessCardHolder->current;
			i++;
			(*count)++;
		}
		businessCardHolder->current = businessCardHolder->current->next;
	}
}
BusinessCard PutOut(BusinessCardHolder *businessCardHolder, BusinessCard *index) {
	BusinessCard businessCard;
	BusinessCard *previous = NULL;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != index) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (previous != NULL) {
		previous->next = index->next;
	}
	else {
		businessCardHolder->first = index->next;
	}
	if (index->next != NULL) {
		businessCardHolder->current = index->next;
	}
	else {
businessCardHolder->current = previous;
	}
	businessCard = *index;
	businessCard.next = NULL;
	if (index != NULL) {
		free(index);
	}
	businessCardHolder->length--;
	return businessCard;
}
BusinessCard *First(BusinessCardHolder *businessCardHolder) {
	businessCardHolder->current = businessCardHolder->first;
	return businessCardHolder->current;
}
BusinessCard *Previous(BusinessCardHolder *businessCardHolder) {
	BusinessCard *previous = NULL;
	BusinessCard *current = NULL;

	current = businessCardHolder->current;
	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL && businessCardHolder->current != current) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (previous != NULL) {
		businessCardHolder->current = previous;
	}

	return businessCardHolder->current;
}
BusinessCard *Next(BusinessCardHolder *businessCardHolder) {
	BusinessCard *previous;

	previous = businessCardHolder->current;
	businessCardHolder->current = businessCardHolder->current->next;
	if (businessCardHolder->current == NULL) {
		businessCardHolder->current = previous;
	}
	return businessCardHolder->current;
}
BusinessCard *Last(BusinessCardHolder *businessCardHolder) {
	BusinessCard *previous = NULL;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	businessCardHolder->current = previous;

	return businessCardHolder->current;
}
void Arrange(BusinessCardHolder *businessCardHolder) {
	Long i = 1;
	Long j;
	BusinessCard *previous;

	while (i < businessCardHolder->length) {
		previous = NULL;
		businessCardHolder->current = businessCardHolder->first;
		j = 1;
		while (j <= businessCardHolder->length - i) {
			if (strcmp(businessCardHolder->current->personal.name, businessCardHolder->current->next->personal.name) > 0) {
				if (previous != NULL) {
					previous->next = businessCardHolder->current->next;
				}
				else {
					businessCardHolder->first = businessCardHolder->current->next;
				}
				previous = businessCardHolder->current->next;
				businessCardHolder->current->next = previous->next;
				previous->next = businessCardHolder->current;
			}
			else {
				previous = businessCardHolder->current;
				businessCardHolder->current = businessCardHolder->current->next;
			}
			j++;
		}
		i++;
	}
}
void Destroy(BusinessCardHolder *businessCardHolder) {
	BusinessCard *next;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		next = businessCardHolder->current->next;
		free(businessCardHolder->current);
		businessCardHolder->current = next;
	}
}
BusinessCard* Move(BusinessCardHolder *businessCardHolder, BusinessCard *index) {
	businessCardHolder->current = index;
	
	return businessCardHolder->current;
}
BusinessCard* FindByCompanyName(BusinessCardHolder *businessCardHolder, char(*companyName)) {
	BusinessCard *index = NULL;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL && strcmp(businessCardHolder->current->company.name, companyName) != 0) {
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (businessCardHolder->current != NULL) {
		index = businessCardHolder->current;
	}
	return index;
}