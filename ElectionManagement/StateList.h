#pragma once
#include "List.h"
#include "State.h"

class PartyList;

class StateList : public List<State*>
{
public:
	~StateList(){}

	void addToTail(State* s);

	Sitizen* findSitizenByID(int ID);
	State* findStateByNum(int num);
	
	void printSitizens();
	void printCase9(PartyList& party_lst);

	void load(istream& in);
};
