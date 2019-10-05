#ifndef _DATE_H
#define _DATE_H

typedef signed short int Short;
enum Month { JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12 };
enum WeekDay { SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6 };
class Date {
public:
	Date(); //����Ʈ ������ Default Constructor
	Date(Short year, Month month, Short day); //�Ű������� ���� ������ Constructor with parameters
	Date(const char(*date)); //�Ű������� ���� ������ Constructor with parameters
	Date(const Date& source); //���� ������ Copy Constructor
	~Date(); //�Ҹ��� Destructor
	static Date Today(); //static ����
	Date Yesterday();
	Date Tomorrow();
	Date PreviousDate(Short days);
	Date NextDate(Short days);
	bool IsEqual(const Date& other);
	bool IsNotEqual(const Date& other);
	bool IsLesserThan(const Date& other);
	bool IsGreaterThan(const Date& other);
	operator char*(); //�� ��ȯ �Լ�
	Date& operator --(); //���� ���� ������ �Լ�
	Date operator --(int); //���� ���� ������ �Լ�
	Date& operator ++(); //���� ���� ������ �Լ�
	Date operator ++(int); //���� ���� ������ �Լ�
	Date operator -(Short days); // ���� ������ �Լ�
	Date operator +(Short days); // ���ϱ� ������ �Լ�
	bool operator ==(const Date& other); // == ������ �Լ�
	bool operator !=(const Date& other); // != ������ �Լ�
	bool operator <(const Date& other); // < ������ �Լ�
	bool operator <=(const Date& other); // <= ������ �Լ�
	bool operator >(const Date& other); // > ������ �Լ�
	bool operator >=(const Date& other); // >= ������ �Լ�
	Date& operator =(const Date& source); //ġȯ ������ �Լ�

	Short GetYear() const;
	Short GetMonth() const;
	Short GetDay() const;
	Short GetWeekDay() const;
private:
	Short year;
	Month month;
	Short day;
	WeekDay weekDay;
};
inline Short Date::GetYear() const {
	return this->year;
}
inline Short Date::GetMonth() const {
	return this->month;
}
inline Short Date::GetDay() const {
	return this->day;
}
inline Short Date::GetWeekDay() const {
	return this->weekDay;
}

#endif //_DATE_H