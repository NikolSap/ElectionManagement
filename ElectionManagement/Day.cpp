#include "Day.h"
#include "mY_exseptions.h"

Day::Day(int month, int day, int year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

bool Day::setDay(int day) 
{
	if (this->month == 2)
	{
		if ((day<1)||(day > 28))
			throw InvalidInputException();
	}
	else if ((day<1)||(day>31))
		throw InvalidInputException();
	this->day = day; 
	return true;
}

bool Day::setMonth(int month)
{
	if ((month > 12) || (month < 1))
		throw InvalidInputException();
	this->month = month;
	return true;
}

bool Day::setYear(int year)
{
	if (year < 0)
		throw InvalidInputException();
	this->year = year; return true;
}

Day& Day::operator=(const Day& s)
{
	this->day = s.day;
	this->month = s.month;
	this->year = s.year;
	return* this;
}

ostream& operator<<(ostream& os, const Day& p)
{
	os << p.day << "/" << p.month << "/" << p.year << endl;
	return os;
}

void Day::save(ostream& out) const
{
	out.write(rcastcc(&this->day), sizeof(this->day));
	out.write(rcastcc(&this->month), sizeof(this->month));
	out.write(rcastcc(&this->year), sizeof(this->year));
}

void Day::load(istream& in)
{
	in.read(rcastc(&this->day), sizeof(this->day));
	in.read(rcastc(&this->month), sizeof(this->month));
	in.read(rcastc(&this->year), sizeof(this->year));
}