#include "PartyList.h"
#include "mY_exseptions.h"



void PartyList::addToTail(Party* p)
{
	List::addToTail(p);
	p->setSerialNum(this->len);
}

void PartyList::inhanceListInParty(State& s)
{
	SitizenListNodeInParty* n = new SitizenListNodeInParty(&s);
	ListNode* curr = this->_head;
	while (curr)
	{
			curr->_data->getList()->addToTail(n);
		curr = curr->_next;
	}
}

Party* PartyList::findPartyByNum(int num)
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

Party* PartyList::winningPartyForState(State* state)
{
	ListNode* curr = this->_head;
	Party* p = curr->_data;
	int votes = curr->_data->getList()->findState(state)->getNumOfVotes();
	curr = curr->_next;
	while (curr)
	{
		int temp= curr->_data->getList()->findState(state)->getNumOfVotes();
		if (temp > votes)
		{
			votes = temp;
			p = curr->_data;
		}
		curr = curr->_next;
	}
	return p;
}

void PartyList::printRepAndVotesForState(State* s)
{
	ListNode* curr = this->_head;
	while (curr)
	{
		SitizenListNodeInParty* node = curr->_data->getList()->findState(s);
		int numOfVotesForPartyInState= node->getNumOfVotes();
		int num_of_votes_in_state=s->getNumOfVotes();


		double pressent_for_party_in_state = numOfVotesForPartyInState * 100 / num_of_votes_in_state;
		int num_of_rep = (pressent_for_party_in_state * s->getNumOfRep() / 100)+0.5;
		curr->_data->setNumOfRep(num_of_rep);
		curr->_data->getList()->findState(s)->setNumofRep(num_of_rep);
		State::Node* n = new State::Node();
		n->num_of_rep = num_of_rep;
		n->p = curr->_data;
		s->getList_party()->addToTail(n);

		node->getData()->PrintXrep(num_of_rep);
		cout << "for party " << curr->_data->getName() << endl;
		cout << "votes: " << node->getNumOfVotes() << endl;
		cout << "pressent of votes: " << (double)node->getNumOfVotes() / s->getNumOfVotes() << endl;
		curr = curr->_next;
	}
}

void PartyList::printCase9(StateList& state_lst)
{
	bubbleSort();
	ListNode* curr = this->_head;
	while (curr)
	{
		cout << "the information of party: " << curr->_data->getName() << "is: " << endl;
		cout << curr->_data->getLeader();
		cout << "num of rep: " << curr->_data->getNumOfRep() << endl;
		cout << "num of votes: " << curr->_data->getNumOfVotes() << endl;
		curr = curr->_next;
	}
}

void PartyList::initializeNumOfRepInParties()
{
	ListNode* curr = this->_head;
	while (curr)
	{

		curr->_data->initRep();
		curr = curr->_next;
	}
}

void PartyList::load(istream& in, StateList& head)
{
	in.read(rcastc(&this->len), sizeof(int));
	if (this->len == 0)
		return;
	ListNode* curr = new ListNode(),*prev=nullptr;
	this->_head = curr;
	curr->_data = new Party();
	curr->_data->load(in, head);
	prev = curr;
	curr = curr->_next;
	for (int i = 1; i < len; i++)
	{
		curr = new ListNode();
		curr->_data = new Party();
		curr->_data->load(in,head);
		curr->_prev = prev;
		prev->_next = curr;
		curr->_next = nullptr;
		prev = curr;
	}
	this->_tail = prev;
}
