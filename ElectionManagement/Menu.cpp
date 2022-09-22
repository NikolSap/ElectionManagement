#define CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include "Day.h"
#include "elctionRound.h"

#include "SitizenList.h"
#include "PartyList.h"
#include "StateList.h"
#include "InPartyList.h"

#include "mY_exseptions.h"

#include <iostream>
#include <fstream>
#include <string>

//#define testtt

class Party;

using namespace std;
#define NUM_OF_NUMBERS_IN_ID 9
#define LEN 100
enum class numOfcase { CASE1 = 1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8, CASE9, CASE10, CASE11, CASE12 };

void optionPrint();
void case1(StateList& state_lst, PartyList& party_lst);
void case2(StateList& state_lst, int type, int election_year);
void case3(PartyList& party_lst, StateList& state_lst);
void case4(PartyList& party_lst, StateList& state_lst, int type);
void case8(PartyList& party_lst, StateList& state_lst);
void case9(PartyList& party_lst, StateList& state_lst);
void case11(const electionRound& r);
void case12(electionRound& r);



void StartMenu(electionRound& r1)
{
	numOfcase opperation;
	int op;
	while (true)
	{
		optionPrint();
		cout << "please enter the opperation number: " << endl;
		cin >> op;
		opperation = static_cast<numOfcase>(op);
		switch (opperation)
		{
		case numOfcase::CASE1:
		{
			try  
			{
				if (r1.getType() == 2)
					cout<< "This is simple election. you can't add a district in this election type."<<endl;
				else
				case1(r1.getStatesInCountry(), r1.getCandidatePartyList());
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
		}
		break;
		case numOfcase::CASE2:
			try {
				case2(r1.getStatesInCountry(), r1.getType(),r1.getDay().getYear());
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case numOfcase::CASE3:
			try {
				case3(r1.getCandidatePartyList(), r1.getStatesInCountry());
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case numOfcase::CASE4:
			try {
				case4(r1.getCandidatePartyList(), r1.getStatesInCountry(),r1.getType());
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case numOfcase::CASE5:
			r1.getStatesInCountry().PrintList();
			break;
		case numOfcase::CASE6:
			r1.getStatesInCountry().printSitizens();
			break;
		case numOfcase::CASE7:
			r1.getCandidatePartyList().PrintList();
			break;
		case  numOfcase::CASE8:
			try {
				case8(r1.getCandidatePartyList(), r1.getStatesInCountry());
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case  numOfcase::CASE9:
			cout << "The date of the election is: " << r1.getDay();
			case9(r1.getCandidatePartyList(), r1.getStatesInCountry());
			break;
		case  numOfcase::CASE10:
			exit(END_OF_PROGRAM);
			break;
		case  numOfcase::CASE11:
			try {
				case11(r1);
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case  numOfcase::CASE12:
			try {
				case12(r1);
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		default:
			cout << "there is no such operation." << endl;
			break;
		}
		cout << endl;
	}
}

void optionPrint()
{
	cout << "the options are as followed:" << endl;
	cout << "1. Add a district." << endl;
	cout << "2. Add a sitizen." << endl;
	cout << "3. Add a party." << endl;
	cout << "4. Add a sitizen as a representative for a party." << endl;
	cout << "5. Print all States." << endl;
	cout << "6. print all sitizens." << endl;
	cout << "7. print all parties." << endl;
	cout << "8. Insert a vote." << endl;
	cout << "9. print election results." << endl;
	cout << "10. exit the program." << endl;
	cout << "11. save current election round." << endl;
	cout << "12. load exsisting election round." << endl;
}

void case1(StateList& state_lst, PartyList& party_lst)
{
	char ch;
	int temp;
	cout << "Plaese enter the type of the state: d for divided and u for united" << endl;
	cin >> ch;
	cout << "please enter the name of the state: " << endl;
	string name;
	cin >> name;
	cout << "Enter the number of representatives: " << endl;
	cin >> temp;
	State* s1 = nullptr;
	if (ch == 'd')
	{
		s1 = new dividedState(name, temp);
		s1->setType('d');
	}
	else
		s1 = new State(name, temp, ch);
	state_lst.addToTail(s1);
	party_lst.inhanceListInParty(*s1);
}

void case2(StateList& state_lst,int type, int election_year)
{
	State* s;
	int id,year,state=1;
	cout << "please enter the name of the sitizen" << endl;
	string name;
	cin >> name;
	cout << "The ID number" << endl;
	cin >> id;
	cout << "The birth year" << endl;
	cin >> year;
	if (type == 1) {
		cout << "The state number" << endl;
		cin >> state;
	}
	s = state_lst.findStateByNum(state);
	try {
		state_lst.findSitizenByID(id);
		throw InvalidInputException();
	}
	catch(std::exception& e){
		if (election_year - year < 18)
			throw InvalidInputException();
		Sitizen* sitizen = new Sitizen(s, id, year, name);
		s->getSitizenList()->addToTail(sitizen);
	}
}

void case3(PartyList& party_lst,StateList& state_lst)
{
	int temp;
	cout << "please enter the name of the Party" << endl;
	string name;
	cin >> name;
	cout << "The leader ID" << endl;
	cin >> temp;
	Sitizen* s = state_lst.findSitizenByID(temp);
	Party* p = new Party(name,s,state_lst);
	party_lst.addToTail(p);
}

void case4(PartyList& party_lst, StateList& state_lst,int type)
{
	int id,state,party;
	Sitizen* sitizen;
	cout << "Please enter ID" << endl;
	cin >> id;
	sitizen = state_lst.findSitizenByID(id);
	cout << "Please enter the party number" << endl;
	cin >> party;
	Party* p =party_lst.findPartyByNum(party);
	if (type == 1)
	{
		cout << "Please enter the state number" << endl;
		cin >> state;
	}
	else
		state = 1;
	State* s = state_lst.findStateByNum(state);
	p->addRep(sitizen, s);
}

void case8(PartyList& party_lst, StateList& state_lst)
{
	int party, id;
	cout << "please enter the sitizens id: " << endl;
	cin >> id;
	cout << "please enter the number of the party: " << endl;
	cin >> party;
	Sitizen* s = state_lst.findSitizenByID(id);
	if (!s)
		throw InvalidInputException();
	Party* p = party_lst.findPartyByNum(party);
	if (s->getDidVoted()==true)
		throw InvalidInputException();
	s->setDidVoted();
	s->getState()->setNumOfVotes();
	p->getList()->addVoteForState(s->getState());
}

void case9(PartyList& party_lst,StateList& state_lst)
{
	state_lst.printCase9(party_lst);
	party_lst.printCase9(state_lst);
	party_lst.initializeNumOfRepInParties();
}

void case11(const electionRound& r)
{
	string fileName;
	cout << "please enter the name of the file to open" << endl;
	cin>>fileName;
	ofstream outfile(fileName);

	if (!outfile) 
		throw LoadFailed();

	r.save(outfile);
	outfile.close();
}

void case12(electionRound& r)
{
	string fileName;
	cout << "Please enter the name of the file" << endl;
	cin >> fileName;
	ifstream infile(fileName);

	if (!infile) 
		throw LoadFailed();

	r.load(infile);
	StartMenu(r);
	infile.close();
}

