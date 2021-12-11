#include"MyActionHandler.h"


void MyActionHandler::onWorkerSend(int minute, ResourceType resource) {

	cout << "W " << minute << ' ';

	if (resource == ResourceType::banana) {
		cout << "banana";
	}
	else {
		cout << "schweppes";
	}
	cout << endl;

}

void MyActionHandler::onWorkerBack(int minute, ResourceType resource) {

	cout << "D " << minute << ' ';

	if (resource == ResourceType::banana) {
		cout << "banana";
	}
	else {
		cout << "schweppes";
	}
	cout << endl;

}

void MyActionHandler::onClientDepart(int index, int minute, int banana, int schweppes) {

	cout << index << ' ' << minute << ' ' << banana << ' ' << schweppes << endl;

}