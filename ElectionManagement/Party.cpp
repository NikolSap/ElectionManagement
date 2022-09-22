#include "Party.h"
#include "SitizenList.h"
#include "StateList.h"

using namespace std;

class Sitizen;
class SitizenList;

Party::Party()
{

}

Party::Party(string name, Sitizen* s,StateList& state_lst)
{
	this->leadder = s;
	this->lst = new InPartyList();
	
	auto node = state_lst.begin();
	for (; node != nullptr; ++node)
	{
		SitizenListNodeInParty* n = new SitizenListNodeInParty(node._ptr->_data);
		this->lst->addToTail(n);
	}

	this->setName(name);
}

void Party::setName(const string name)
{
	this->name = name;
}

void Party::setLeader(Sitizen* s)
{
	this->leadder = s;
}

void Party::setNumOfVotes()
{
	(this->numOfVotes)++;
}

void Party::setSerialNum(int num)
{
	this->serialNum = num;
}

void Party::setNumOfRep(int num)
{
	this->numOfRep += num;
}

Sitizen* Party::getLeader() const
{
	return this->leadder;
}

const string Party::getName() const
{
	return this->name;
}

ostream& operator<<(ostream& os, const Party& p)
{
	os << "The information of this party is: " << endl;
	os << "Serial number: " << p.serialNum << endl;
	os << "Name: " << p.name << endl;
	os << "Leader: " << p.leadder;
	os << endl;
	os << "Representative:  " << endl;
	os << p.lst << endl;

	return os;
}

void Party::addRep(Sitizen* sitizen, State* state)
{
	this->getList()->addSitizenAsRep(sitizen, state);
}

Party& Party::operator=(const Party& s)
{
	this->leadder = s.leadder;
	this->lst = s.lst;
	this->numOfRep = s.numOfRep;
	this->numOfVotes = s.numOfVotes;
	this->serialNum = s.serialNum;
	this->setName(s.name);
	return *this;
}

void Party::initRep()
{
	this->numOfRep = 0;
}

void Party::save(ostream& out) const
{
	int size = this->name.size();
	out.write(rcastcc(&this->numOfRep), sizeof(int));
	out.write(rcastcc(&size), sizeof(int));
	out.write(rcastcc(&this->name[0]), size);
	this->lst->save(out);
	int id = this->leadder->getId();
	out.write(rcastcc(&id), sizeof(id));
}

void Party::load(istream& in, StateList& state)
{
	int len;
	in.read(rcastc(&this->numOfRep), sizeof(int));
	in.read(rcastc(&len), sizeof(int));
	if(len>0) ////////
		this->name.resize(len + 1);
	in.read(rcastc(&this->name[0]), len);
	this->lst = new InPartyList();
	this->lst->load(in,state);
	in.read(rcastc(&len), sizeof(int));
	this->leadder = state.findSitizenByID(len);
}