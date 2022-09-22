#pragma once
#include "Day.h"
#include "PartyList.h"
#include "StateList.h"

class Day;

class electionRound {

private:
	int type;
	//1-regular election
	//2-simple election
	Day& _d;
	PartyList candidatePartyList;
	StateList statesInTheCountry;

public:
	electionRound(Day& d, int type);
	virtual ~electionRound() {}

	PartyList& getCandidatePartyList() { return this->candidatePartyList; }
	StateList& getStatesInCountry() { return this->statesInTheCountry; }
	int getType() const { return this->type; }
	const Day& getDay() const { return this->_d; }
	
	bool setType(int t);
	bool setDate(const Day& d) { this->_d = d; return true; }

	void save(ostream& out) const;
	void load(istream& in);

};