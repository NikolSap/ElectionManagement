#pragma once
#include <iostream>
#include "Party.h"
#include "SitizenList.h"
#include <string>
#include "List.h"

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class SitizenList;
class StateListNode;
class Party;

class State {

protected:
	friend class PartyList;
	string name;
	int stateNum;
	SitizenList* lst;/*list of all the sitizen in the state*/
	int numOfVotes;
	int numOfRep;
	char type;

public:
	class Node {	//List of num of rep for party? n each node--> party, num of rep
	public:
		Party* p;
		int num_of_rep ;
		int getValueForSort()const  {return num_of_rep;}
	};

	List<Node*>* lst_party;

public:
	State();
	State(string name, int numOfRep, char type);
	~State();

	void setType(char type);
	void setName(string name);
	void setNumOfRep(int num);
	void setNumOfVotes();
	void setSerialNum(int num);

	List<Node*>* getList_party() const { return this->lst_party; }

	virtual char getType()const;
	string getName() const;
	int getSerialNum() const;
	int getNumOfVotes() const;
	int getNumOfRep() const;
	SitizenList* getSitizenList() const;

	friend ostream& operator<<(ostream&, const State& st);
	void operator=(const State& st);
	bool operator==(const State& st);

	void save(ostream& out) const;
	void load(istream& in);
};