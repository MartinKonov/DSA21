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
	vector<Employee*> employees;

	Employee(string name, vector<Employee*> employees, Employee* boss = nullptr, Employee* colleague = nullptr) {

		this->name = name;

		for (size_t i = 0; i < employees.size(); i++) {
			this->employees.push_back(employees[i]);
		}
		this->boss = boss;
		this->colleague = colleague;
	}

	void insert_employee(Employee* emp) {

		this->employees.push_back(emp);

	}

};