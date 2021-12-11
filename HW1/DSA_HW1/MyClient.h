#pragma once
#include"../DSA_ HW1_TESTS/interface.h"


struct MyClient : public Client{

	int index;
	bool hasBeenServiced = 0;


	MyClient(int ar_min, int bananacnt, int schweppescnt, int maxWTime, int index)   {
		
		this->arriveMinute = ar_min;
		this->banana = bananacnt;
		this->schweppes = schweppescnt;
		this->maxWaitTime = ar_min + maxWTime;
		this->index = index;
	}

};

