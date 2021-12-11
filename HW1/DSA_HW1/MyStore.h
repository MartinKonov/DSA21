#pragma once
#include "../DSA_ HW1_TESTS/interface.h"
#include"Worker.h"
#include<vector>
#include"MyClient.h"
#include<stdexcept>
#include"Simple_queue.h"
#include<algorithm>

using std::invalid_argument;
using std::vector;


struct MyStore : Store {
private:

	ActionHandler* actionHandler = nullptr;
	size_t time = 0;
	size_t bananasCount;
	size_t spriteCount;
	simple_queue clients;
	vector<MyClient> waiting_cliets;
	vector<MyWorker> workers;

public:
	vector<int> important_minutes;

	MyStore();

	MyStore(int workerCount, int startBanana, int startSchweppes);
	
	MyStore(MyStore& other) = delete;

	MyStore& operator= (MyStore& other) = delete;


public:
	void setActionHandler(ActionHandler* handler) override;

	void init(int workerCount, int startBanana, int startSchweppes) override;

	void addClients(const Client* clients, int count) override;

	virtual int getBanana() const;

	virtual int getSchweppes() const;

	void advanceTo(int minute) override;


private:
	bool workersReturn(size_t CurTime);

	void setWorkers(size_t count);

	size_t WorkersAvailableCount();
	
	void sendWorker(ResourceType resource, size_t CurTime);

	bool WorkerWillBeBackWithNeededAmountSprite(MyClient* client);

	bool WorkerWillBeBackWithNeededAmountBananas(MyClient* client);

	size_t countOfNeededWorkersForBananas(MyClient* client);

	size_t countOfNeededWorkersForSprite(MyClient* client);

	void WorkerHandler(size_t CurTime, MyClient* client);


private:
	size_t clientsEnterStore(size_t CurTime);
	
	void serviceClients(size_t CurTime);
	
	void RemoveFromWaitingList(MyClient* Client);
	
	void ClientDepartureWhenMaxWait(size_t CurTime);
	
	void ClientLeave(MyClient* Client, size_t CurTime);
	
	double clientNeededSprite(MyClient* client);

	double clientNeededBananas(MyClient* client);

	void swap(int* first, int* second);

	int partition(int lower_index, int higher_index);

	void quickSort(int lower_index, int higher_index);

};


