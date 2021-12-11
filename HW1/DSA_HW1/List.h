#pragma once
#include"MyClient.h"


struct node {

	MyClient data;
	node* next;
	node* prev;

	node(MyClient client, node* next = nullptr, node* prev = nullptr) :data(client), next(next), prev(prev)
	{}

};

class list {

	node* head;
	node* tail;
	size_t size;

public:
	list() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	~list() {
		while (this->size != 0) {
			this->pop_front();
		}
	}

	void push_back(MyClient client) {

		if (head == nullptr) {
			head = new node(client);
			this->tail = this->head;
		}
		else {
			this->tail->next = new node(client, tail);
			this->tail = tail->next;
		}
		this->size++;
	}

	void pop_front() {

		if (size == 0) {
			return;
		}
		if (this->head == this->tail) {
			delete this->head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			this->head = this->head->next;
			delete this->head->prev;
			this->head->prev = nullptr;
		}
		this->size--;
	}

	MyClient front() {
		return this->head->data;
	}

	size_t getSize() {
		return this->size;
	}
};