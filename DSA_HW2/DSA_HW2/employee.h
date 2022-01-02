#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector; 

struct Employee
{
	string name;
	Employee* boss;
	Employee* colleague;
	Employee* employee;
	size_t employee_count = 0;
	size_t level = 0;
	bool hasBeenPassed = 0;

	Employee() {
		this->boss = nullptr;
		this->colleague = nullptr;
		this->employee = nullptr;
		this->name = "Uspeshnia";
	}

	Employee(string nm, Employee* bos, Employee* col = nullptr, Employee* emp = nullptr) : boss(bos), colleague(col), employee(emp) {
		this->name = nm;
	}

};