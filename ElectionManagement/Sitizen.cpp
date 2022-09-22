#include "Sitizen.h"
#include "StateList.h"
#include "mY_exseptions.h"

using namespace std;

Sitizen::Sitizen()
{
	this->name = "";
	this->id = 0;
	this->year = 0;
	this->state = nullptr;
}

Sitizen::Sitizen(State* s,int id)
	:state(s)
{
	this->name = "";
	setId(id);
	this->year = 0;
}

Sitizen::Sitizen(State* s, int id, int year, string name)
	:state(s)
{
		this->setName(name);
		setId(id);
		this->year = year;
}

int Sitizen::countNumOfDigits(int num)
{
	int count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

void Sitizen::setName(string name)
{
	this->name = name;
}

void Sitizen::setId(int id)
{
	int n=countNumOfDigits(id);
	if (n != 9)
		throw InvalidInputException();
	this->id = id;
}

void Sitizen::setYear(int year)
{
	this->year = year;
}

void Sitizen::setState(State* s)
{
	this->state = s;
}

void Sitizen::setSerialNum(int num)
{
	this->serialNum = num;
}

void Sitizen::setDidVoted()
{
	this->didVoted = true;
}

int Sitizen::getYear() const
{
	return this->year;
}

int Sitizen::getId() const
{
	return this->id;
}

State* Sitizen::getState() const
{
	return this->state;
}

ostream& operator<<(ostream& os, const Sitizen& s)
{
	os << "The name of the sitizen is: " << s.name << endl;
	os << "The ID is: " << s.id << endl;
	os << "The birth year is:  " << s.year << endl;
	return os;
}

Sitizen& Sitizen::operator=(const Sitizen& s)
{
	this->id = s.id;
	this->setName(s.name);
	this->year = s.year;
	this->state = s.state;
	return *this;
}

Sitizen& Sitizen::operator*(Sitizen* s)
{
	return *this;
}

bool Sitizen::operator==(const Sitizen& s)
{
	if (s.id != this->id)// in case 2,we check if the id was already used--> hence for each id only one sitizen.
		return false;
	return true;
}

void Sitizen::save(ostream& out) const
{
	int size = this->name.size();
	out.write(rcastcc(&this->id), sizeof(int));
	out.write(rcastcc(&this->year), sizeof(int));
	out.write(rcastcc(&size), sizeof(int));
	out.write(rcastcc(&this->name[0]), size);
	int num = this->state->getSerialNum();
	out.write(rcastcc(&num), sizeof(int));
	out.write(rcastcc(&this->didVoted), sizeof(bool));

}

void Sitizen::load(istream& in, State* head)
{
	int len;
	in.read(rcastc(&this->id), sizeof(int));
	in.read(rcastc(&this->year), sizeof(int));
	in.read(rcastc(&len), sizeof(int));
	this->name.resize(len + 1);
	in.read(rcastc(&this->name[0]), len);

	this->state = head;
	
	in.read(rcastc(&len), sizeof(int));
	
	in.read(rcastc(&this->didVoted), sizeof(bool));
}

//void Sitizen::load(istream& in, StateList& state_lst)
//{
//	int len,stateNum;
//	in.read(rcastc(&this->id), sizeof(int));
//	in.read(rcastc(&this->year), sizeof(int));
//	in.read(rcastc(&len), sizeof(int));
//	in.read(rcastc(&stateNum), sizeof(int));
//	this->state = state_lst.findStateByNum(stateNum);
//	in.read(rcastc(&this->didVoted), sizeof(bool));
//}