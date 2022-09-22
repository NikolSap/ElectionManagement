#include "SitizenList.h"
#include "mY_exseptions.h"
#include "StateList.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

Sitizen* SitizenList::findSitizenByID(int ID)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		if (curr->_data->getId() == ID)
			return curr->_data;
		curr = curr->_next;
	}
	return nullptr;
}

void SitizenList::PrintXrep(int x)
{
	int i;
	ListNode* curr = this->_head;
	for (i = 0; curr&&i < x; i++)
	{
		cout << *(curr->_data) << endl;
		curr = curr->_next;
	}
	if (i != x)
		throw NotEnoughtRepInParty();
}

void SitizenList::saveSitizensById(ostream& out)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		int id = curr->_data->getId();
		out.write(rcastcc(&id), sizeof(int));
		curr = curr->_next;
	}

}

void SitizenList::loadSitizenById(istream& in,int num, StateList& state_lst)
{
	for(int i = 0; i < num; i++)
	{
		ListNode* curr = new ListNode();
		curr->_next = curr->_prev = nullptr;
		int id;
		in.read(rcastc(&id), sizeof(int));
		this->addToTail(state_lst.findSitizenByID(id));
	}
}

void SitizenList::load(istream& in, State* head)
{
	in.read(rcastc(&this->len), sizeof(int));
	if(this->len == 0)
		return;
	ListNode* curr = new ListNode(),*prev=nullptr;
	this->_head = curr;
	curr->_data = new Sitizen();
	curr->_data->load(in, head); 
	prev = curr;
	curr = curr->_next;
	for (int i = 1; i < len; i++)
	{
		curr = new ListNode();
		curr->_data = new Sitizen();
		curr->_data->load(in,head);
		curr->_prev = prev;
		prev->_next = curr;
		curr->_next = nullptr;
		prev = curr;
	}
	this->_tail = curr;
	this->_tail->_next = nullptr;
}
