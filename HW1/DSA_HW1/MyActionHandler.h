#pragma once
#include"../DSA_ HW1_TESTS/interface.h"
#include<iostream>
using std::cout;
using std::endl;

struct MyActionHandler : ActionHandler {

	void onWorkerSend(int minute, ResourceType resource) override;

	void onWorkerBack(int minute, ResourceType resource) override;

	void onClientDepart(int index, int minute, int banana, int schweppes) override;


};
