#include"interface.h"

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {

	this->Uspeshnia = r.Uspeshnia;
	this->tree = r.tree;
}

Hierarchy::Hierarchy(const Hierarchy& r) {

	this->Uspeshnia = r.Uspeshnia;
	this->tree = r.tree;
}

Hierarchy::Hierarchy(const string& data) {

	vector<string> employees;

	unpack_employees(&employees, data);

	if (employees.size() == 1) {
		throw std::invalid_argument("Error string! Try again in the format: (boss_name)-(employee_name)\n");
	}
	if (!employees.empty()) {
		this->tree.size = 1;
	}
	this->Uspeshnia = new Employee("Uspeshnia",nullptr);
	for (size_t i = 1; i < employees.size(); i++) {


		if (i % 2 != 0) {
			
			if (employees[i - 1] == this->Uspeshnia->name) {

				this->tree.insert(employees[i], this->Uspeshnia->name, this->Uspeshnia);

			}
			else {
				if (!tree.find(employees[i - 1], this->Uspeshnia)) {
					throw std::invalid_argument("Your input was invalid. Try again!\n");
				}
				
				this->tree.insert(employees[i], employees[i-1], this->Uspeshnia);
				
			}
		}
		i++;
	}
}

Hierarchy::~Hierarchy() noexcept {

	this->tree.deltree(this->Uspeshnia);
	delete this->Uspeshnia;

}

string Hierarchy::print()const {

	const Employee* uspeshen = this->Uspeshnia;
	return this->tree.printTree(uspeshen);

}

void Hierarchy::unpack_employees(vector<string>* to_unpack, const string& data) {

	size_t sz = data.size();

	string name;

	for (size_t i = 0; i < sz; i++) {

		if (data[i] == ' ') {
			continue;
		}

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

int Hierarchy::longest_chain()const {

	if (this->tree.size == 0) {
		return 0;
	}
	const Employee* uspeshen = this->Uspeshnia;
	int toReturn = this->tree.height(uspeshen);
	return toReturn;

}

bool Hierarchy::find(const string& name) const {

	if (this->tree.size == 0) {
		return false;
	}
	const Employee* uspeshen = this->Uspeshnia;
	bool toReturn = this->tree.find(name, uspeshen);
	return toReturn;

}

int Hierarchy::num_employees() const {

	return this->tree.size;

}

int Hierarchy::num_overloaded(int level) const {
	int counter = 0;
	this->tree.count_overloaded(level, Uspeshnia, counter);
	return counter;
}

string Hierarchy::manager(const string& name) const {

	return this->tree.name_of_boss(name, this->Uspeshnia);

}

int Hierarchy::num_subordinates(const string& name) const {

	if (!this->tree.find(name, this->Uspeshnia)) {
		return -1;
	}

	return this->tree.count_employees(name, this->Uspeshnia);

}

unsigned long Hierarchy::getSalary(const string& who) const {

	if (!this->tree.find(who, this->Uspeshnia)) {
		return -1;
	}

	const Employee* uspeshen = this->Uspeshnia;
	const Employee* person = this->tree.curEmployee(who, uspeshen);

	return this->tree.paycheck(person, uspeshen);

}

bool Hierarchy::fire(const string& who) {

	return this->tree.fire(who, this->Uspeshnia);

}

bool Hierarchy::hire(const string& who, const string& boss) {

	if (!tree.find(boss, Uspeshnia)) {
		return 0;
	}

	return this->tree.insert(who, boss, this->Uspeshnia);

}

Hierarchy Hierarchy::join(const Hierarchy& right) const {

	Hierarchy* ToMerge = new Hierarchy("");
	Tree* toInsert = &ToMerge->tree;
	bool exit_rec = 0;

	if (this->tree.size > right.tree.size) {
		const Employee* uspeshen = this->Uspeshnia;
		const Employee* drugiq_uspeshen = right.Uspeshnia;
		this->tree.merge(&right.tree, right.Uspeshnia,uspeshen, *toInsert, ToMerge->Uspeshnia, exit_rec);
		right.tree.fillRestOfOther(*toInsert, ToMerge->Uspeshnia, drugiq_uspeshen);
	}
	else {
		const Employee* uspeshen = right.Uspeshnia;
		right.tree.merge(&this->tree, this->Uspeshnia,uspeshen, *toInsert, ToMerge->Uspeshnia, exit_rec);
		this->tree.fillRestOfOther(*toInsert, ToMerge->Uspeshnia, this->Uspeshnia);
	}
	if (exit_rec == 1) {
		delete ToMerge;
		Hierarchy ToReturn("");
		return ToReturn;
	}
	ToMerge->tree.size++;
	return *ToMerge;
}

void Hierarchy::incorporate() {

	int height = this->tree.height(this->Uspeshnia) - 1;

	this->tree.startincorporate(this->Uspeshnia, height);

}

void Hierarchy::modernize() {

	int height = this->tree.height(this->Uspeshnia) - 1;

	this->tree.startmodernize(Uspeshnia, Uspeshnia, height);


}