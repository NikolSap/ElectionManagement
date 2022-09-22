#pragma once

#include "List.h"
#include "SitizenListNodeInParty.h"
#include "State.h"

class SitizenListNodeInParty;
class State;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class InPartyList : public List<SitizenListNodeInParty*>
{
public:
	~InPartyList() {}

	void addSitizenAsRep(Sitizen* s, State* state);
	void addVoteForState(State* s);

	int getNumOfVotesForState(State* s);

	SitizenListNodeInParty* findState(State* s);

	void load(istream& in, StateList& state);
};
