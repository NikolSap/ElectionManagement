#include "elctionRound.h"
#include <iostream>
#include "mY_exseptions.h"
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

electionRound::electionRound(Day& d, int type)
	:_d(d)
{
	setType(type);
}

bool electionRound::setType(int type)
{
	if ((type != 1) && (type != 2))
		throw InvalidInputException();
	else this->type = type;
	return true;
}

void electionRound::save(ostream& out) const
{
	out.write(rcastcc(&(this->type)), sizeof(this->type));
	this->_d.save(out);
	this->statesInTheCountry.save(out);
	this->candidatePartyList.save(out);
}

void electionRound::load(istream& in)
{
	in.read(rcastc(&this->type), sizeof(this->type));
	this->_d.load(in);
	this->statesInTheCountry.load(in);
	StateList& s = this->statesInTheCountry;
	this->candidatePartyList.load(in, s);
}
