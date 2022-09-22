#pragma once
#include <iostream>
#include <string>

using namespace std;

class State;
class StateList;

class Sitizen {

protected:
	string name;
	int id;
	int year;
	State* state;
	int serialNum = 0;
	bool didVoted = false;
	

	int countNumOfDigits(int num);

public:

	Sitizen();
	Sitizen(State* s,int id);
	Sitizen(State* s, int id, int year, string name);
	~Sitizen() {}

	void setName(string name);
	void setId(int id);
	void setYear(int year);
	void setState(State* s);
	void setSerialNum(int num);
	void setDidVoted();

	string getName() const { return this->name; }
	int getYear() const;
	int getId() const;
	State* getState() const;
	bool getDidVoted() const { return this->didVoted; }

	int getSerialNum() const { return this->serialNum; }

	friend std::ostream& operator<<(std::ostream&, const Sitizen& s);
	Sitizen& operator=(const Sitizen& s);
	Sitizen& operator*(Sitizen* s);
	bool operator==(const Sitizen& s);

	void save(ostream& out) const;
	void load(istream& in, State* head);


	void load(istream& in, StateList& state_lst);

};