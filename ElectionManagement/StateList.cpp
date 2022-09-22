#include "StateList.h"
#include "PartyList.h"
#include "mY_exseptions.h"

void StateList::addToTail(State* s)
{
	List::addToTail(s);
	s->setSerialNum(this->len);
}

Sitizen* StateList::findSitizenByID(int ID)
{
	Sitizen* s = nullptr;
	ListNode* curr = this->_head;
	while (!s&&curr)
	{
		s = curr->_data->getSitizenList()->findSitizenByID(ID);
		curr = curr->_next;
	}
	if (!s)
		throw DataNotFound();
	return s;
}

State* StateList::findStateByNum(int num)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		if (curr->_data->getSerialNum() == num)
			return curr->_data;
		curr = curr->_next;
	}
	throw DataNotFound();
}

void StateList::printSitizens()
{
	ListNode* curr = this->_head;
	while (curr)
	{
		curr->_data->getSitizenList()->PrintList();
		curr = curr->_next;
	}
}

void StateList::printCase9(PartyList& party_lst)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		cout << "The information of this state is: " << endl;
		cout << "Name: " << curr->_data->getName() << endl;
		cout << "Number of representatives: " << curr->_data->getNumOfRep() << endl;

		party_lst.printRepAndVotesForState(curr->_data);
		curr->_data->getList_party()->bubbleSort();
		if ((curr->_data->getType()) == 'u')
		{
			Party* party = party_lst.winningPartyForState(curr->_data);
			cout << "Leader: " << party->getLeader() << endl;
			party->setNumOfRep(curr->_data->getNumOfRep());
		}
		else {
			State* s = curr->_data;
			s->getList_party()->bubbleSort();
			auto node = s->getList_party()->begin();
			for (; node != nullptr; ++node)
				if (node._ptr->_data->num_of_rep > 0)
					cout << node._ptr->_data->p->getLeader();
			}
		if (curr->_data->getNumOfVotes() == 0)
			throw DivByZeroError();
		cout << "The pressent of votes in the state: " << (double)curr->_data->getSitizenList()->getLen()/curr->_data->getNumOfVotes() << endl;
		
		
		curr = curr->_next;
	}
}

void StateList::load(istream& in)
{
	in.read(rcastc(&this->len), sizeof(int));
	if (this->len == 0)
		return;
	ListNode* curr = new ListNode(),*prev=nullptr;
	this->_head = curr;
	curr->_data = new State();
	curr->_data->load(in);
	prev = curr;
	curr = curr->_next;
	for (int i = 1; i < len; i++)
	{
		curr = new ListNode();
		curr->_data = new State();
		curr->_data->load(in);
		curr->_prev = prev;
		prev->_next = curr;
		curr->_next = nullptr;
		prev = curr;
	}
	this->_tail = prev;
}
