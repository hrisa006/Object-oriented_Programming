#include <iostream>

struct Date {
	int day;
	int month;
	int year;
};

void checkDate(const Date& date)
{
	if()
}


void toNextDay(const Date& date)
{
	int newDay = 0;
	int newMonth = date.month;
	int newYear = 0;
	if ((date.day == 31 && (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) || date.day == 28 || date.day == 29 || date.day == 30)
	{
		newDay = 1;
		newMonth = date.month + 1;
	}
	else{
		newDay = date.day + 1;
	}
	std::cout << newDay << "." << newMonth << "." << date.year << std::endl;
}

int substractDates(const Date& date1, const Date& date2)
{
	return date2.day - date1.day;
}


int main()
{
	std::cout << "Enter a date:\nday: ";
	Date date;
	std::cin >> date.day;
	std::cout << "month: ";
	std::cin >> date.month;
	std::cout << "year: ";
	std::cin >> date.year;

	std::cout << "The next date is: ";
	toNextDay(date);

	std::cout << "Enter another date to find the substraction between them two: ";
	Date date2;
	std::cin >> date2.day;
	std::cout << "month: ";
	std::cin >> date2.month;
	std::cout << "year: ";
	std::cin >> date2.year;

	std::cout << "=> " << substractDates(date, date2) << " days";

	return 0;
}
