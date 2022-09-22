#pragma once

#include <iostream>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class Day
{
private:
	int	day;
	int	month;
	int year;

public:
	Day(int month, int day, int year);
	Day(const Day& d)
		:day(d.day), month(d.month), year(d.year) {}
	~Day() {}

	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	int getDay() const { return this->day; }
	int getMonth() const { return this->month; }
	int getYear() const { return this->year; }

	Day& operator=(const Day& s);
	friend ostream& operator<<(ostream&, const Day& p);

	void save(ostream& out) const;
	void load(istream& in);

};

