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
	size_t level;


	Employee() {
		this->boss = nullptr;
		this->colleague = nullptr;
		this->employee = nullptr;
		this->name = "Uspeshnia";
	}

	Employee(string nm) {
		this->boss = nullptr;
		this->colleague = nullptr;
		this->employee = nullptr;
		this->name = nm;
	}

	~Employee() {
		//this->name.clear();
		this->employee_count = 0;
		this->level = 0;
	}
};