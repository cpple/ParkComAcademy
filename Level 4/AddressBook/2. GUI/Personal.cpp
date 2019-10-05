#include "Personal.h"

Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("") {
}
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	:name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress){
}
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address), telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress){
}
Personal::~Personal() {
}
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator ==(const Personal& other) {
	bool ret = false;
	
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}

	return ret;
}
bool Personal::operator !=(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}

	return ret;
}
Personal& Personal::operator =(const Personal& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}
#if 0
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
	//����Ʈ ������
	Personal me;
	cout << me.GetName() << "/" << me.GetAddress() << "/" << me.GetTelephoneNumber() << "/" << me.GetEmailAddress() << endl;
	//�Ű������� ���� ������
	Personal somebody("ȫ�浿", "����� ������", "0101111", "hong@");
	cout << somebody.GetName() << "/" << somebody.GetAddress() << "/" << somebody.GetTelephoneNumber() << "/" << somebody.GetEmailAddress() << endl;
	//���� ������
	Personal somesomebody(somebody);
	cout << somesomebody.GetName() << "/" << somebody.GetAddress() << "/" << somebody.GetTelephoneNumber() << "/" << somebody.GetEmailAddress() << endl;
	//IsEqual ���� �Լ�
	bool ret = somesomebody.IsEqual(somebody);
	if (ret == true) {
		cout << "���� ���" << endl;
	}
	//==������ �Լ�
	if (somesomebody == somebody) {
		cout << "���� ���" << endl;
	}

	Personal meme("��浿", "����� ���빮��", "0102222", "kim@");
	cout << meme.GetName() << "/" << meme.GetAddress() << "/" << meme.GetTelephoneNumber() << "/" << meme.GetEmailAddress() << endl;
	//ġȯ ������ �Լ�
	me = meme;
	cout << me.GetName() << "/" << me.GetAddress() << "/" << me.GetTelephoneNumber() << "/" << me.GetEmailAddress() << endl;
	//IsNotEqual ���� �Լ�
	ret = me.IsNotEqual(somebody);
	if (ret == true) {
		cout << "�ٸ� ���" << endl;
	}
	//!=������ �Լ�
	if (me != somebody) {
		cout << "�ٸ� ���" << endl;
	}

	return 0;
}
#endif