#include <iostream>
#include"../DSA_ HW1_TESTS/interface.h"
#include"MyStore.h"
#include"MyActionHandler.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {

	size_t workercount, startBanana = 0, startsprite = 0, clientsCount;
	MyStore store;
	MyActionHandler handler;
	vector<Client> clients;
	string answer;
	cout << "Would you like to initialise the starting bananas and schweppes of your store? Y/N :" << endl;
	cin >> answer;

	if (answer == "Y") {
		cout << endl << "Enter the starting bananas count: ";
		cin >> startBanana;
		cout << endl << "Enter the starting schweppes count: ";
		cin >> startsprite;
		cout << endl;
	}

	cout << "Enter the worker count of your store: ";
	cin >> workercount;
	

	store.init(workercount, startBanana, startsprite);
	store.setActionHandler(&handler);

	cout << "Enter the amount of clients that will enter your store: ";
	cin >> clientsCount;
	cout << endl;

	for (int i = 0; i < clientsCount; i++) {
		cout << "Enter the arrive minute, desired bananas count, desired schweppes count and the maximal waiting time of client number " << i  << ':' << endl;
		size_t arrive_minute, bananas, sprite, maxWaitTime;
		cin >> arrive_minute >> bananas >> sprite >> maxWaitTime;
		Client a;
		a.arriveMinute = arrive_minute;
		a.banana = bananas;
		a.schweppes = sprite;
		a.maxWaitTime = maxWaitTime;
		clients.push_back(a);

	}
	cout << endl << endl << "Results:" << endl << endl;

	store.addClients(clients.data(), clients.size());


	store.advanceTo(store.important_minutes[store.important_minutes.size() - 1]);


}