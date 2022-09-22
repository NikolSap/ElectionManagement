#include "State.h"
#include "SitizenList.h"
#include "mY_exseptions.h"

using namespace std;

State::State()
{
	this->name = "";
	this->type = 'd';
	this->numOfRep = 0;
	this->numOfVotes = 0;
	this->stateNum = 0;
	this->lst = new SitizenList();
	this->lst_party = new List<Node*>();
}

State::State(string name, int numOfRep,char type)
{
	this->setName(name);
	setNumOfRep(numOfRep);
	this->numOfVotes = 0;
	this->stateNum = 0;
	setType(type);
	this->lst = new SitizenList();
	this->lst_party = new List<Node*>();
}

State::~State()
{
	lst = nullptr;
}

void State::setType(char type)
{
	if((type!='u')&&(type!='d'))
		throw InvalidInputException();
	this->type = type;
}

void State::setName(string name)
{
	this->name = name;
}

void State::setNumOfRep(int num)
{
	if (num < 0)
		throw InvalidInputException();
	this->numOfRep = num;
}

void State::setNumOfVotes()
{
	(this->numOfVotes)++;
}

void State::setSerialNum(int num)
{
	this->stateNum = num;
}

string State::getName() const
{
	return this->name;
}

int State::getSerialNum() const
{
	return this->stateNum;
}

char State::getType()const
{
	return this->type;
}

int State::getNumOfVotes() const
{
	return this->numOfVotes;
}

int State::getNumOfRep() const
{
	return this->numOfRep;
}

SitizenList* State::getSitizenList() const
{
	return this->lst;
}

ostream& operator<<(ostream& os, const State& st)
{
	os << "The information of this State is: " << endl;
	os << "Type: " << typeid(st).name() + 6 << endl;
	os << "Serial number: " << st.getSerialNum() << endl;
	os << "Name: " << st.name << endl;
	os << "Num of rep: " << st.numOfRep << endl;
	return os;
}

void State::operator=(const State& st)
{
	this->numOfRep = st.numOfRep;
	this->numOfVotes = st.numOfVotes;
	this->stateNum = st.stateNum;
	this->setName(st.name);
	this->lst = st.lst;
}

bool State::operator==(const State& st)
{
	if (this->numOfRep != st.numOfRep)
		return false;
	if (this->numOfVotes != st.numOfVotes)
		return false;
	if (this->stateNum != st.stateNum)
		return false;
	if (!(this->lst == st.lst))
		return false;
	if (st.type == 1)
	{
		if (this->name==st.name)
			return false;
	}
	return true;
}

void State::save(ostream& out_file) const
{
	int size = this->name.size();
	out_file.write(rcastcc(&size), sizeof(int));
	out_file.write(rcastcc(&this->name[0]), size);
	out_file.write(rcastcc(&this->stateNum), sizeof(this->stateNum));
	out_file.write(rcastcc(&this->numOfRep), sizeof(this->numOfRep));
	out_file.write(rcastcc(&this->numOfVotes), sizeof(this->numOfVotes));
	out_file.write(rcastcc(&this->type), sizeof(this->type));
	this->lst->save(out_file);
}

void State::load(istream& in_file)
{
	int size;
	in_file.read(rcastc(&size), sizeof(size));
	this->name.resize(size+1);
	in_file.read(rcastc(&this->name[0]), size);
	in_file.read(rcastc(&(this->stateNum)), sizeof(this->stateNum));
	in_file.read(rcastc(&(this->numOfRep)), sizeof(this->numOfRep));
	in_file.read(rcastc(&(this->numOfVotes)), sizeof(this->numOfVotes));
	in_file.read(rcastc(&(this->type)), sizeof(this->type));
	this->lst = new SitizenList();
	this->lst->load(in_file, this);
}

