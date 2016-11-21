#include"Date.h"
#include "Voice.h"

//Data
Date::Date(unsigned int year, unsigned int month, unsigned int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

Date::Date(string yearMonthDay)
{
	istringstream date(yearMonthDay);
	string y, m, d;
	int Year, Month, Day;
	char slash = '/';
	while (slash == '/' && !date.eof())
	{
		getline(date, y, '/');
		getline(date, m, '/');
		getline(date, d, '/');
	}
	Year = stoi(y);
	Month = stoi(m);
	Day = stoi(d);
	if (slash != '/')
		cout << "\nInvalid input!\n";
	else
	{
		this->year = Year;
		this->month = Month;
		this->day = Day;
	}
}

void Date::setYear(unsigned int year)
{
	this->year = year;
}

void Date::setMonth(unsigned int month)
{
	this->month = month;
}

void Date::setDay(unsigned int day)
{
	this->day = day;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}

unsigned int Date::getYear()
{
	return year;
}

unsigned int Date::getMonth()
{
	return month;
}

unsigned int Date::getDay()
{
	return day;
}

string Date::getDate()
{
	stringstream y, m, d;
	y << year;
	m << month;
	d << day;
	return y.str() + '/' + m.str() + '/' + d.str();
}

void Date::show()
{
	stringstream y, m, d;
	y << year;
	m << month;
	d << day;
	cout << y.str() + '/' + m.str() + '/' + d.str() << endl;
}

unsigned int Date::numDays(unsigned int month, unsigned int year)
{
	if (month % 2 != 0)
		return 31;
	else
		if (month != 2)
			return 30;
		else
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				return 29;
			else
				return 28;
}

bool Date::isValid()
{
	if (day > numDays(month, year) || day < 1)
		return false;
	else
		return true;
}

bool Date::isEqualTo(const Date &date)
{
	if (date.day == day && date.month == month && date.year == year)
		return true;
	else
		return false;
}

bool Date::isNotEqualTo(const Date &date)
{
	if (!isEqualTo(date))
		return true;
	else
		return false;
}

bool Date::isAfter(const Date &date)
{
	if (date.year > year)
		return true;
	else
		if (date.year == year)
			if (date.month == month && date.day > day)
				return true;
			else
				if (date.month > month)
					return true;
				else
					return false;
		else
			return false;
}

bool Date::isBefore(const Date &date)
{
	if (!isAfter(date))
		return true;
	else
		return false;
}
