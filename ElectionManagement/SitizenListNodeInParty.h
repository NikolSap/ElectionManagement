#pragma once
#include "SitizenList.h"
#include "State.h"
#include<iostream>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class SitizenListNodeInParty
{

private:
	SitizenList* data;
	int serialNum = 0;
	int numOfRep = 0;
	State* state = nullptr;
	int numOfVotes = 0;

public:
	SitizenListNodeInParty();
	SitizenListNodeInParty(State* s);
	~SitizenListNodeInParty() { this->state = nullptr; delete this->data; }

	void setData(SitizenList* data);
	void setSerialNum(int num);
	void setNumofRep(int num);
	void setVotes();
	void setState(State* s);

	int getSerialNum() const { return this->serialNum; }
	SitizenList* getData() const { return this->data; }
	int getNumOfVotes() { return this->numOfVotes; }
	int getNumofRep() { return this->numOfRep; }
	State* getState() const { return this->state; }

	friend ostream& operator<<(ostream&, const SitizenListNodeInParty& p);

	void save(ostream& out) const;
	void load(istream& in, StateList& state);
};
