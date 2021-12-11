#include "MyStore.h"

MyStore::MyStore() {
	this->bananasCount = 0;
	this->spriteCount = 0;

}

MyStore::MyStore(int workerCount, int startBanana, int startSchweppes) {

	if (workerCount < 0 || startBanana < 0 || startSchweppes < 0) {
		throw invalid_argument("Mystore::MyStore()");
	}


	setWorkers(workerCount);
	this->bananasCount = startBanana;
	this->spriteCount = startSchweppes;
}

void MyStore::setActionHandler(ActionHandler* handler)  {
		actionHandler = handler;
}

void MyStore::init(int workerCount, int startBanana, int startSchweppes)  {

	if (workerCount < 0 || startBanana < 0 || startSchweppes < 0) {
		throw std::invalid_argument("MyStore::init");
	}

	setWorkers(workerCount);
	this->bananasCount = startBanana;
	this->spriteCount = startSchweppes;

}

void MyStore::addClients(const Client* clients, int count)  {
	if (count < 0) {
		throw invalid_argument("MyStore::addClients");
	}
	for (size_t i = 0; i < count; i++) {
		Client a = clients[i];
		MyClient b(a.arriveMinute, a.banana, a.schweppes, a.maxWaitTime, i);

		this->important_minutes.push_back(b.arriveMinute);
		this->important_minutes.push_back(b.arriveMinute + 60);
		this->important_minutes.push_back(b.maxWaitTime);

		this->clients.push(b);
	}
	quickSort(0, important_minutes.size() - 1);
}

int MyStore::getBanana() const {
	return this->bananasCount;
}

int MyStore::getSchweppes() const {
	return this->spriteCount;
}

void MyStore::advanceTo(int minute)  {
	
	if (minute < 0 || minute < this->time) {
		throw invalid_argument("MyStore::advanceTo");
	}
	else {

		size_t i = 0;


		if (important_minutes.empty()) {
			return;
		}

		while (important_minutes[i] <= minute) {

			bool WorkerHasReturned = false;
			if (this->important_minutes[i] >= 60) {
				WorkerHasReturned = workersReturn(this->important_minutes[i]);

			}

			size_t count_entered = clientsEnterStore(this->important_minutes[i]);

			if (count_entered > 0) {
				for (size_t j = 0; j < count_entered; j++) {
					serviceClients(this->important_minutes[i]);
				}
			}

			if (waiting_cliets.size() > 0) {
				ClientDepartureWhenMaxWait(this->important_minutes[i]);
			}

			if (WorkerHasReturned) {
				serviceClients(this->important_minutes[i]);
			}

			if (i == this->important_minutes.size() - 1) {
				break;
			}
			else {
				i++;
			}
		}
		
		this->time = minute;
	}
}



bool MyStore::workersReturn(size_t CurTime) {
	bool hasReturned = false;

	for (size_t i = 0; i < this->workers.size(); i++) {

		if (this->workers[i].occupied && this->workers[i].timåOfreturn == CurTime) {

			if (workers[i].type == ResourceType::banana) {
				this->bananasCount += 100;
			}
			else {
				this->spriteCount += 100;
			}

			workers[i].occupied = false;

			this->actionHandler->onWorkerBack(CurTime, workers[i].type);
			hasReturned = true;
		}
	}
	return hasReturned;
}

void MyStore::setWorkers(size_t count) {

	MyWorker a;
	for (size_t i = 0; i < count; i++) {
		this->workers.push_back(a);
	}

}

size_t MyStore::WorkersAvailableCount() {
	int counter = 0;
	for (size_t i = 0; i < this->workers.size(); i++) {

		if (!(workers[i].occupied)) {
			counter++;
		}
	}
	return counter;
}

void MyStore::sendWorker(ResourceType resource, size_t CurTime) {

	for (size_t i = 0; i < this->workers.size(); i++) {
		if (!(this->workers[i].occupied)) {

			this->workers[i].occupied = true;
			this->workers[i].timeOfDeparture = CurTime;
			this->workers[i].timåOfreturn = CurTime + 60;
			this->workers[i].type = resource;
			this->actionHandler->onWorkerSend(CurTime, resource);
			return;
		}
	}

}

bool MyStore::WorkerWillBeBackWithNeededAmountSprite(MyClient* client) {
	size_t sumSprite = 0;

	for (size_t i = 0; i < workers.size(); i++) {
		if (workers[i].occupied) {

			if (workers[i].timåOfreturn <= client->maxWaitTime) {
				if (workers[i].type == ResourceType::schweppes) {
					sumSprite += 100;
				}
			}


		}
	}

	if (sumSprite + this->spriteCount >= client->schweppes) {
		return true;
	}
	return false;

}

bool MyStore::WorkerWillBeBackWithNeededAmountBananas(MyClient* client) {

	size_t sumBananas = 0;


	for (size_t i = 0; i < workers.size(); i++) {
		if (workers[i].occupied) {

			if (workers[i].timåOfreturn <= client->maxWaitTime) {
				if (workers[i].type == ResourceType::banana) {
					sumBananas += 100;
				}
			}


		}
	}
	if (sumBananas + this->bananasCount >= client->banana) {
		return true;
	}

	return false;
}

size_t MyStore::countOfNeededWorkersForBananas(MyClient* client) {

	return ceil(clientNeededBananas(client) / 100);

}

size_t MyStore::countOfNeededWorkersForSprite(MyClient* client) {

	return ceil(clientNeededSprite(client) / 100);

}

void MyStore::WorkerHandler(size_t CurTime, MyClient* client) {


	size_t availableWorkers = WorkersAvailableCount();

	if (availableWorkers > 0) {

		if (client->banana >= client->schweppes && client->banana > this->bananasCount) {
			if (!WorkerWillBeBackWithNeededAmountBananas(client)) {

				size_t count_needed_workers_bananas = countOfNeededWorkersForBananas(client);

				if (count_needed_workers_bananas > 0) {

					if (count_needed_workers_bananas <= availableWorkers) {

						for (size_t i = 0; i < count_needed_workers_bananas; i++) {
							sendWorker(ResourceType::banana, CurTime);
						}
						availableWorkers = WorkersAvailableCount();

					}
					else if (count_needed_workers_bananas > availableWorkers) {

						for (size_t i = 0; i < availableWorkers; i++) {
							sendWorker(ResourceType::banana, CurTime);
						}
						availableWorkers = WorkersAvailableCount();
					}
				}
			}
			if (!WorkerWillBeBackWithNeededAmountSprite(client)) {

				size_t count_needed_workers_sprite = countOfNeededWorkersForSprite(client);

				if (count_needed_workers_sprite > 0) {

					if (count_needed_workers_sprite <= availableWorkers) {

						for (size_t i = 0; i < count_needed_workers_sprite; i++) {
							sendWorker(ResourceType::schweppes, CurTime);
						}
						availableWorkers = WorkersAvailableCount();
					}
					else if (count_needed_workers_sprite > availableWorkers) {

						for (size_t i = 0; i < availableWorkers; i++) {
							sendWorker(ResourceType::schweppes, CurTime);
						}
						availableWorkers = WorkersAvailableCount();
					}
				}
			}

		}
		else {
			if (!WorkerWillBeBackWithNeededAmountSprite(client)) {

				size_t count_needed_workers_sprite = countOfNeededWorkersForSprite(client);

				if (count_needed_workers_sprite > 0) {

					if (count_needed_workers_sprite <= availableWorkers) {

						for (size_t i = 0; i < count_needed_workers_sprite; i++) {
							sendWorker(ResourceType::schweppes, CurTime);
						}
						availableWorkers = WorkersAvailableCount();
					}
					else if (count_needed_workers_sprite > availableWorkers) {

						for (size_t i = 0; i < availableWorkers; i++) {
							sendWorker(ResourceType::schweppes, CurTime);
						}
						availableWorkers = WorkersAvailableCount();
					}
				}
			}

			size_t count_needed_workers_bananas = countOfNeededWorkersForBananas(client);

			if (count_needed_workers_bananas > 0) {

				if (count_needed_workers_bananas <= availableWorkers) {

					for (size_t i = 0; i < count_needed_workers_bananas; i++) {
						sendWorker(ResourceType::banana, CurTime);
					}
					availableWorkers = WorkersAvailableCount();

				}
				else if (count_needed_workers_bananas > availableWorkers) {

					for (size_t i = 0; i < availableWorkers; i++) {
						sendWorker(ResourceType::banana, CurTime);
					}
					availableWorkers = WorkersAvailableCount();
				}
			}
		}
	}
	client->hasBeenServiced = true;
}



size_t MyStore::clientsEnterStore(size_t CurTime) {
	size_t counter = 0;
	for (size_t i = 0; i < this->clients.size(); i++) {

		if (clients.front().arriveMinute == CurTime) {

			this->waiting_cliets.push_back(clients.front());
			this->clients.pop();
			i--;
			counter++;
		}
		else {
			break;
		}
	}
	return counter;
}

void MyStore::serviceClients(size_t CurTime) {

	for (size_t i = 0; i < this->waiting_cliets.size(); i++) {

		if (waiting_cliets[i].banana <= this->bananasCount && waiting_cliets[i].schweppes <= this->spriteCount) {

			this->bananasCount -= waiting_cliets[i].banana;
			this->spriteCount -= waiting_cliets[i].schweppes;

			ClientLeave(&waiting_cliets[i], CurTime);
			i--;
		}
		else {
			if (waiting_cliets[i].hasBeenServiced == 0) {
				WorkerHandler(CurTime, &waiting_cliets[i]);
			}
		}


	}
}

void MyStore::RemoveFromWaitingList(MyClient* Client) {

	for (size_t i = 0; i < this->waiting_cliets.size(); i++) {
		if (&waiting_cliets[i] == Client) {
			waiting_cliets.erase(waiting_cliets.begin() + i);
		}
	}
}

void MyStore::ClientDepartureWhenMaxWait(size_t CurTime) {

	for (size_t i = 0; i < waiting_cliets.size(); i++) {

		if (waiting_cliets[i].maxWaitTime == CurTime) {

			if (waiting_cliets[i].banana >= this->bananasCount) {

				waiting_cliets[i].banana = bananasCount;
				this->bananasCount = 0;

			}
			else {
				this->bananasCount -= waiting_cliets[i].banana;
			}

			if (waiting_cliets[i].schweppes >= this->spriteCount) {

				waiting_cliets[i].schweppes = this->spriteCount;
				this->spriteCount = 0;

			}
			else {
				this->spriteCount -= waiting_cliets[i].schweppes;
			}

			ClientLeave(&waiting_cliets[i], CurTime);

		}

	}

}

void MyStore::ClientLeave(MyClient* Client, size_t CurTime) {

	this->actionHandler->onClientDepart(Client->index, CurTime, Client->banana, Client->schweppes);
	RemoveFromWaitingList(Client);

}

double MyStore::clientNeededSprite(MyClient* client) {

	if (client->schweppes == 0) {
		return 0;
	}

	size_t sumSprite = 0;
	for (size_t i = 0; i < workers.size(); i++) {
		if (workers[i].occupied) {

			if (workers[i].timåOfreturn <= client->maxWaitTime) {
				if (workers[i].type == ResourceType::schweppes) {
					sumSprite += 100;
				}
			}
		}
	}
	return client->schweppes - (sumSprite + this->spriteCount);
}

double MyStore::clientNeededBananas(MyClient* client) {

	if (client->banana == 0) {
		return 0;
	}

	size_t sumBananas = 0;
	for (size_t i = 0; i < workers.size(); i++) {
		if (workers[i].occupied) {

			if (workers[i].timåOfreturn <= client->maxWaitTime) {
				if (workers[i].type == ResourceType::banana) {
					sumBananas += 100;
				}
			}
		}
	}
	return client->banana-(sumBananas + this->bananasCount);

}

void MyStore::swap(int* first, int* second) {
	size_t temp = *first;
	*first = *second;
	*second = temp;
}

int MyStore::partition(int lower_index, int higher_index) {

	int pivot = this->important_minutes[higher_index];
	int ind_of_smaller_el = lower_index - 1;


	for (size_t i = lower_index; i <= higher_index - 1; i++) {

		if (this->important_minutes[i] < pivot) {

			ind_of_smaller_el++;

			swap(&this->important_minutes[ind_of_smaller_el], &this->important_minutes[i]);
		}
	}

	swap(&this->important_minutes[ind_of_smaller_el + 1], &this->important_minutes[higher_index]);

	return ind_of_smaller_el + 1;
}

void MyStore::quickSort(int lower_index, int higher_index) {

	if (lower_index < higher_index) {

		int part = partition(lower_index, higher_index);

		quickSort(lower_index, part - 1);
		quickSort(part + 1, higher_index);
	}

}