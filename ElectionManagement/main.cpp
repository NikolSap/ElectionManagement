//#include <iostream>
#include "Menu.h"
#include "elctionRound.h"
#include <fstream>
#include "dividedState.h"
#include <string>

enum class numOfcase1 { CASE1 = 1, CASE2, CASE3};
void case12(electionRound& r);

int main()
 {
	bool flag = true;
	int typeElection=1;
	int year, month, day, op;
	
	cout << "1. new ellection round" << endl;
	cout << "2. load existing election round" << endl;
	cout << "3. exit the program" << endl;
	cout << "please enter the opperation number: " << endl;
	cin >> op;
	numOfcase1 opperation = static_cast<numOfcase1>(op);

	opperation = static_cast<numOfcase1>(op);
	while (flag) {
		flag = false;
		switch (opperation)
		{
		case numOfcase1::CASE1:
			std::cout << "please enter the elction date. day the month and then year: " << endl;
			std::cin >> day >> month >> year;
			cout << "please enter type election: 1 for regular election or 2 for simple election:" << endl;
			cin >> typeElection;
			try {
				Day date(day, month, year);
				electionRound r(date, typeElection);
				if (r.getType() == 2)
				{
					State* s2 = new dividedState();
					s2->setType('d');
					try {
						r.getStatesInCountry().addToTail(s2);
					}
					catch (std::exception& e)
					{
						cout << e.what() << endl;
					}
				}
				StartMenu(r);
			}
			catch(string msg) {
				cout << msg << endl;
				flag = true;
			}
			break;
		case numOfcase1::CASE2:
			try {
				Day d(1, 1, 1);
				electionRound r(d, typeElection);
				case12(r);
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
				flag = true;
			}
			break;
		case numOfcase1::CASE3:
			exit(END_OF_PROGRAM);
		default:
			flag = true;
			cout << "There is no such operation." << endl;
			break;
		}
	}
	return true;
}




