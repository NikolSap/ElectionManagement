#pragma once
#include <iostream>
#include "List.h"
#include "InPartyList.h"
#include <string>

using namespace std;

class Sitizen;
class State;
class InPartyList;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


class Party {

private:
	string name;
	Sitizen* leadder=nullptr;
	int serialNum = 0;
	int numOfRep = 0;
	int numOfVotes = 0;

	InPartyList* lst;

public:
	Party();
	Party(string name, Sitizen* s,StateList& state_lst);
	~Party() { delete lst; }
	Party(Party& other):leadder(other.leadder) {*this = other;}

	void setName(const string name);
	void setLeader(Sitizen* s);
	void setSerialNum(int num);
	void setNumOfRep(int num);
	void setNumOfVotes();

	void initRep();

	int getValueForSort() const { return this->numOfRep; }
	Sitizen* getLeader() const;
	const string getName() const;
	int getSerialNum() const { return this -> serialNum; }
	int getNumOfRep() const { return this->numOfRep; }
	InPartyList* getList() const { return this->lst; }
	int getNumOfVotes() const { return this->numOfVotes; }
	friend ostream& operator<<(ostream&, const Party& p);

	void addRep(Sitizen* sitizen, State* state);

	Party& operator=(const Party& s);

	void save(ostream& out) const;
	void load(istream& in, StateList& state);

};