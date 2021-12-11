#pragma once
#include"List.h"
#include<vector>

class simple_queue {

	list queue;

public:
	size_t size(){
		return queue.getSize();
	}

	void push(MyClient client) {
		this->queue.push_back(client);
	}

	void pop() {
		this->queue.pop_front();
	}

	MyClient front() {
		return this->queue.front();
	}
	
};