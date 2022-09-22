#include "InPartyList.h"
#include "mY_exseptions.h"

void InPartyList::addSitizenAsRep(Sitizen* s, State* state)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		if (curr->_data->getState()->getSerialNum() == state->getSerialNum())
		{
			curr->_data->getData()->addToTail(s);
			return;
		}
		curr = curr->_next;
	}
}

void InPartyList::addVoteForState(State* s)
{
	ListNode* curr = this->_head;
	while(curr)
	{
		if (curr->_data->getState() == s)
			curr->_data->setVotes();
		curr = curr->_next;
	}
}

int InPartyList::getNumOfVotesForState(State* s)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		if (curr->_data->getState() == s)
			return curr->_data->getNumOfVotes();
		curr = curr->_next;
	}
	throw DataNotFound();
}

SitizenListNodeInParty* InPartyList::findState(State* s)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		if (curr->_data->getState()->getSerialNum() == s->getSerialNum())
			return curr->_data;
		curr = curr->_next;
	}
	throw DataNotFound();
}

void InPartyList::load(istream& in, StateList& state)
{
	in.read(rcastc(&this->len), sizeof(int));
	if (len == 0)
		return;
	ListNode* curr = new ListNode(),*prev=nullptr;
	this->_head = curr;
	curr->_data = new SitizenListNodeInParty();
	curr->_data->load(in, state);
	prev = curr;
	curr = curr->_next;
	for (int i = 1; i < len; i++)
	{
		curr = new ListNode();
		curr->_data = new SitizenListNodeInParty();
		curr->_data->load(in, state);
		prev = curr;
		curr = curr->_next;
	}
	this->_tail = prev;
}