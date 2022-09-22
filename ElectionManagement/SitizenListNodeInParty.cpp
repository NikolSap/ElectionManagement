#include "SitizenListNodeInParty.h"
#include "StateList.h"


SitizenListNodeInParty::SitizenListNodeInParty()
{
	this->data = new SitizenList();

}

SitizenListNodeInParty::SitizenListNodeInParty(State* s)
	:state(s) 
{
	this->data = new SitizenList();
}

void SitizenListNodeInParty::setData(SitizenList* data)
{
	this->data = data;
}

void SitizenListNodeInParty::setSerialNum(int num)
{
	this -> serialNum = num;
}

void SitizenListNodeInParty::setNumofRep(int num)
{
	this->numOfRep = num;
}

void SitizenListNodeInParty::setVotes()
{
	(this->numOfVotes)++;
}

void SitizenListNodeInParty::setState(State* s)
{
	this->state = s;
}

ostream& operator<<(ostream& os, const SitizenListNodeInParty& p)
{
	os << "The information of this list is: " << endl;
	os << "State: " << p.state << endl;
	os << "Serial number: "<<p.serialNum<< endl;
	os << "Num of representatives: "<< p.numOfRep << endl;
	os << "Number of votes: " << p.numOfVotes << endl;
	return os;
}

void SitizenListNodeInParty::save(ostream& out) const
{
	int len = this->data->getLen();
	out.write(rcastcc(&len), sizeof(int));
	this->data->saveSitizensById(out);
	int num = this->state->getSerialNum();
	out.write(rcastcc(&this->numOfRep), sizeof(int));
	out.write(rcastcc(&this->numOfVotes), sizeof(int));
	out.write(rcastcc(&this->serialNum), sizeof(int));
	out.write(rcastcc(&num), sizeof(int));

}

void SitizenListNodeInParty::load(istream& in, StateList& state)
{
	int num,len;
	in.read(rcastc(&len), sizeof(int));
	this->data = new SitizenList();
	this->data->loadSitizenById(in, len, state);
	in.read(rcastc(&this->numOfRep), sizeof(int));
	in.read(rcastc(&this->numOfVotes), sizeof(int));
	in.read(rcastc(&this->serialNum), sizeof(int));
	in.read(rcastc(&num), sizeof(int));
	this->state = state.findStateByNum(num);
}
