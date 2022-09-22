#pragma once

#include "List.h"
#include "Party.h"

class PartyList : public List<Party*>
{
public:
	~PartyList() {}

	void addToTail(Party* p);

	void inhanceListInParty(State& s);
	Party* findPartyByNum(int num);
	Party* winningPartyForState(State* state);
	void printRepAndVotesForState(State* s);
	void printCase9(StateList& state_lst);

	void initializeNumOfRepInParties();
	virtual void load(istream& in, StateList& head);

};
