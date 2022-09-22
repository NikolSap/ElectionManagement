#pragma once
#include "List.h"
#include "Sitizen.h"

class SitizenList : public List<Sitizen*>
{
public:
	~SitizenList() {}

	Sitizen* findSitizenByID(int ID);
	void PrintXrep(int x);

	virtual void load(istream& in, State* head);
	void saveSitizensById(ostream& out);
	void loadSitizenById(istream& in,int num, StateList& state_lst);

};