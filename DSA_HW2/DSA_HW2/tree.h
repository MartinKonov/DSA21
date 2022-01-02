#pragma once
#include<stdexcept>
#include"pair.h"
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>


class Tree {

	std::vector<Employee*> allEmployees;

public:
	int size;
	
	Tree();

	~Tree();

	void deltree(Employee*& first);

	bool find(const string person, const Employee* first)const;

	bool insert(string person, string boss, Employee* first);
	
	//returns the count of immidiate employees of an Employee with the given name.
	int count_employees(const string name_of_person, const Employee* first)const;
	
	//returns the name of the manager of the Employee with the given name.
	string name_of_boss(const string name_of_person, const Employee* first)const;

	bool fire(string name_of_person, Employee* first);

	size_t height(const Employee* first)const;

	void count_descendants(const Employee* person, int &counter)const;

	void count_overloaded(int n, const Employee* first, int& count)const ;

	unsigned long paycheck(const Employee* person, const Employee* first)const;

	void delPairs(vector<pair*>& pairs)const;
	
	string printTree(const Employee* first)const;
	
	//returns true if Employee* el exists in q, returns false if not.	
	bool InQueue(std::queue<const Employee*> q, Employee* el)const;
	
	//returns true of the Employee with the given name exists in the tree
	//using this->allEmployees
	bool InTree(string el)const;
	
	//sorts pairs, first by manager name, then by employee name
	void sortPairs(vector<pair*>& pairs)const;
	
	//turns the pairs (manager) (employee) into a single string.
	string fillString(vector<pair*>& pairs)const;

	void fillPairs(const Employee* first, vector<pair*>& pairs)const;
	
	//returns the Employee with the given name in the tree.
	Employee* curEmployee(string name, Employee* first);
	const Employee* curEmployee(string name, const Employee* first)const;

	//returns true if the given person is an employee of the given boss in the tree.
	//returns false if not
	bool isEmployee(const string person, const string boss, const Employee* first)const;

	void merge(const Tree* other, const Employee* other_first ,const Employee* first, Tree& merged, Employee* merged_first, bool& exit_rec)const;

	//merge starts with the Hierarchy which has the bigger number of employees.
	//fillRestOfOther is used to check if the Hierarchy which has the smaller
	//number of employees has any employees, who are not shared between the two
	//hierarchies. If there are, then adds them in the merged Hierarchy.
	void fillRestOfOther(Tree& merged, Employee* merged_first, const Employee* first)const;

	//fills the vector with the highest payed immidiate worker/s of a given boss.
	void HighestPayedWorker(Employee* boss, vector<Employee*>* highest_payed_people);

	//Increments the levels in the Hierarchy for all of the employees(immidiate or not)
	//of a manager.
	void incLevels(Employee* boss_employee);
	
	void setNewBoss(Employee* temp, Employee* highestPayedEmployee);

	void incorporate(Employee* first, int& height);
	
	void startincorporate(Employee* first, int& height);

	void startmodernize(Employee* first, Employee* uspeshen, int& height);

	void incHasBeenPassed(Employee* boss_employee, bool inc);

	void modernize(Employee* first, Employee* uspeshen, int& height, bool& isFired);

};