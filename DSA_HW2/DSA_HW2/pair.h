#pragma once
#include <string>;
#include "Employee.h" 
using std::string;

struct pair {
	
	const Employee* person;
	const Employee* boss;


	pair(const Employee* name_person, const Employee* name_boss) : person(name_person), boss(name_boss) {}

};