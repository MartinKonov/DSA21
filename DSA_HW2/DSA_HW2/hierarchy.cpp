#include"../DSA_HW2_TEST/interface.h"

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {

	//this->size = r.size;
	this->Uspeshnia = r.Uspeshnia;
	this->tree = r.tree;
}

Hierarchy::Hierarchy(const Hierarchy& r) {
	//this->size = r.size;
	this->Uspeshnia = r.Uspeshnia;
	this->tree = r.tree;
}


Hierarchy::Hierarchy(const string& data) {

	vector<string> employees;

	unpack_employees(&employees, data);

	
	for (size_t i = 1; i < employees.size(); i++) {

		Employee* person = new Employee(employees[i]);

		if (i % 2 != 0) {
			
			if (employees[i - 1] == this->Uspeshnia.name) {

				this->tree.insert(person, &this->Uspeshnia, &this->Uspeshnia, 1);
			}
			else {
				Employee* bos = this->tree.curEmployee(employees[i - 1] , &this->Uspeshnia);
				this->tree.insert(person, bos, &this->Uspeshnia, 1);
			}

		}
		i++;
		
	}

}

Hierarchy::~Hierarchy() noexcept {

	this->tree.~Tree();

	//for (size_t i = 0; i < this->employees.size(); i++) {

	//	Employee* person = this->tree.curEmployee(employees[i], &Uspeshnia);
	//	if (!person) {
	//		continue;
	//	}
	//	else {
	//		delete person;
	//	}

	//}

}

void Hierarchy::unpack_employees(vector<string>* to_unpack, const string& data) {

	size_t sz = data.size();

	string name;

	for (size_t i = 0; i < sz; i++) {

		if (data[i] != '-' && data[i] != '\n') {
			name += data[i];
		}
		else {
			to_unpack->push_back(name);
			name.clear();
		}

		if (i == sz - 1 && !name.empty()) {
			to_unpack->push_back(name);
			name.clear();
		}
	}
}

//void Hierarchy::unpack_employees(const string& data) {
//	size_t sz = data.size();
//
//	string name;
//
//	for (size_t i = 0; i < sz; i++) {
//
//		if (data[i] != '-' && data[i] != '\n') {
//			name += data[i];
//		}
//		else {
//			this->employees.push_back(name);
//			name.clear();
//		}
//
//		if (i == sz - 1 && !name.empty()) {
//			this->employees.push_back(name);
//			name.clear();
//		}
//	}
//}

int Hierarchy::longest_chain()const {

	const Employee* uspeshen = &this->Uspeshnia;
	int toReturn = this->tree.height(uspeshen);
	return toReturn;

}

bool Hierarchy::find(const string& name) const {

	const Employee* uspeshen = &this->Uspeshnia;
	bool toReturn = this->tree.find(name, uspeshen);
	return toReturn;

}

int Hierarchy::num_employees() const {

	return this->tree.getSize();

}

int Hierarchy::num_overloaded(int level) const {
	int counter = 0;
	this->tree.count_overloaded(level, &Uspeshnia, counter);
	return counter;
}

string Hierarchy::manager(const string& name) const {

	return this->tree.name_of_boss(name, &this->Uspeshnia);

}

int Hierarchy::num_subordinates(const string& name) const {

	return this->tree.count_employees(name, &this->Uspeshnia);

}

unsigned long Hierarchy::getSalary(const string& who) const {

	const Employee* uspeshen = &this->Uspeshnia;
	const Employee* person = this->tree.curEmployee(who, uspeshen);

	return this->tree.paycheck(person, uspeshen);

}


bool Hierarchy::fire(const string& who) {

	return this->tree.fire(who, &this->Uspeshnia);

}

bool Hierarchy::hire(const string& who, const string& boss) {

	Employee* person = new Employee(who);
	Employee* bos = this->tree.curEmployee(boss, &this->Uspeshnia);

	return this->tree.insert(person, bos, &this->Uspeshnia, 1);

}

string Hierarchy::print()const {

	const Employee* uspeshen = &this->Uspeshnia;
	return this->tree.printTree(uspeshen);

}

Hierarchy Hierarchy::join(const Hierarchy& right) const {

	Hierarchy* ToMerge = new Hierarchy("");
	Tree* toInsert = &ToMerge->tree;
	bool exit_rec = 0;

	if (this->tree.getSize() > right.tree.getSize()) {
		const Employee* uspeshen = &this->Uspeshnia;
		const Employee* drugiq_uspeshen = &right.Uspeshnia;
		this->tree.merge(&right.tree, &right.Uspeshnia,uspeshen, *toInsert, &ToMerge->Uspeshnia, exit_rec);
		right.tree.fillRestOfOther(*toInsert, &ToMerge->Uspeshnia, drugiq_uspeshen);
	}
	else {
		const Employee* uspeshen = &right.Uspeshnia;
		right.tree.merge(&this->tree, &this->Uspeshnia,uspeshen, *toInsert, &ToMerge->Uspeshnia, exit_rec);
		this->tree.fillRestOfOther(*toInsert, &ToMerge->Uspeshnia, uspeshen);
	}

	return *ToMerge;
}


