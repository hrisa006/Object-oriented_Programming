#include <iostream>

struct Date {
	int day;
	int month;
	int year;
};

bool leapYear(int year) {
	if (year % 4 == 0 && year % 100 != 0) {
		return true;
	}
	else if (year % 400 == 0) {
		return true;
	}
	else return false;
}

int yearDaysCounter(const Date& date) {
	int counterDays = 0;
	int year = 1;

	while (year < date.year) {
		if (!leapYear(year)) {
			counterDays += 365;
		}
		else {
			counterDays += 366;
		}
		year++;
	}

	return counterDays;
}

int monthConverter(int month, int year) {
	switch (month) {
	case 1:
		return 31; break;
	case 2:
		if (!leapYear(year)) {
			return 28; break;
		}
		else return 29; break;
	case 3:
		return 31; break;
	case 4:
		return 30; break;
	case 5:
		return 31; break;
	case 6:
		return 30; break;
	case 7:
		return 31; break;
	case 8:
		return 31; break;
	case 9:
		return 30; break;
	case 10:
		return 31; break;
	case 11:
		return 30; break;
	case 12:
		return 31; break;
	default:
		break;
	}
}

int monthDaysCounter(const Date& date) {
	int counterDays = 0;
	int month = 1;

	while (month < date.month) {
		counterDays += monthConverter(month, date.year);
		month++;
	}

	return counterDays;
}

bool checkDate(const Date& date) {
	if (date.day == NULL || date.month == NULL || date.year == NULL) {
		return false;
	}

	if (date.day >= 1 && date.day <= monthConverter(date.month, date.year)) {
		return true;
	}
	else return false;
}

void toNextDay(const Date& date) {
	int newDay = date.day;
	int newMonth = date.month;
	int newYear = date.year;

	if (date.day == monthConverter(date.month, date.year)) {
		newDay = 1;
		if (date.month == 12) {
			newMonth = 1;
			newYear++;
		} 
		else {
			newMonth++;
		}
	} 
	else {
		newDay++;
	}

	std::cout << newDay << "." << newMonth << "." << newYear << std::endl;
}

int substractDates(const Date& date1, const Date& date2) {
	int daysCounter1 = 0;
	int daysCounter2 = 0;

	daysCounter1 = date1.day + monthDaysCounter(date1) + yearDaysCounter(date1);
	daysCounter2 = date2.day + monthDaysCounter(date2) + yearDaysCounter(date2);

	if (daysCounter2 > daysCounter1) {
		return daysCounter2 - daysCounter1;
	}
	else {
		return daysCounter1 - daysCounter2;
	}	
}

int main() {
	std::cout << "Enter a date:\nday: ";
	Date date;
	std::cin >> date.day;
	std::cout << "month: ";
	std::cin >> date.month;
	std::cout << "year: ";
	std::cin >> date.year;

	if (!checkDate(date)) {
		std::cout << "You have entered empty values for the date! Please try again!\n";

		std::cout << "day: ";
		std::cin >> date.day;
		std::cout << "month: ";
		std::cin >> date.month;
		std::cout << "year: ";
		std::cin >> date.year;
	}
	
	std::cout << "The next date is: ";
	toNextDay(date);
	
	std::cout << "Enter another date to find the substraction between them two:\n";
	Date date2;
	std::cout << "day: ";
	std::cin >> date2.day;
	std::cout << "month: ";
	std::cin >> date2.month;
	std::cout << "year: ";
	std::cin >> date2.year;

	if (!checkDate(date2)) {
		std::cout << "You have entered empty values for the date! Please try again!\n";

		std::cout << "day: ";
		std::cin >> date2.day;
		std::cout << "month: ";
		std::cin >> date2.month;
		std::cout << "year: ";
		std::cin >> date2.year;
	}

	std::cout << "=> " << substractDates(date, date2) << " days\n";

	return 0;
}