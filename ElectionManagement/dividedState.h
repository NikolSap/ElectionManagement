#pragma once
#include "State.h"
#include <iostream>
using namespace std;

class dividedState :public State
{
public:

	dividedState(string name, int numofrep) :State(name, numofrep,'d'){}
	dividedState() {}

	virtual char getType() const { return this->type; }
};
