#include"tree.h"



Tree::Tree() {
	this->size = 1;
}

Tree::~Tree() {
	this->size = 0;
}

int Tree::getSize()const {
	
	return this->size;

}

bool Tree::find(const string person, const Employee* first)const {

	if (person.empty() || !first) {
		return false;
	}

	if (first->name == person) {
		return true;
	}

	return find(person, first->colleague) || find(person, first->employee);

}

bool Tree::insert(Employee* person,Employee* boss, Employee* first, bool lvl_change) {

	if (!person || !first) {
		return false;
	}
	if (lvl_change) {
		this->level++;
	}
	if (first->name == boss->name) {
		size_t lvl = this->level;
		this->level = 0;
		person->level = lvl;
		if (!person->boss) {

			if (boss->employee_count == 0) {
				boss->employee_count++;
				boss->employee = person;
				person->boss = boss;
			}
			else {
				Employee* temp = boss->employee;
				while (temp->colleague != nullptr) {
					temp = temp->colleague;
				}
				temp->colleague = person;
				boss->employee_count++;
				person->boss = boss;
			}
			this->size++;
			this->allEmployees.push_back(person);
			return true;
		}
	}

	return insert(person, boss, first->colleague, 0) || insert(person, boss, first->employee, 1);

}

int Tree::count_employees(const string name_of_person, const Employee* first)const {

	if (!first) {
		return false;
	}

	if (name_of_person == first->name) {
		return first->employee_count;
	}

	if (count_employees(name_of_person, first->colleague)) {
		return count_employees(name_of_person, first->colleague);
	}
	else {
		return count_employees(name_of_person, first->employee);
	}
}

string Tree::name_of_boss(const string name_of_person,const Employee* first)const {

	if (!first) {
		return "";
	}

	if (name_of_person == "Uspeshnia") {
		return "";
	}


	if (name_of_person == first->name) {
		return first->boss->name;
	}

	if (name_of_boss(name_of_person, first->colleague) != "") {
		return name_of_boss(name_of_person, first->colleague);
	}
	else {
		return name_of_boss(name_of_person, first->employee);
	}
}

bool Tree::fire(string name_of_person, Employee* first) {

	if (!find(name_of_person, first)) {
		return 0;
	}

	if (name_of_person.empty() || !first) {
		return false;
	}

	if (name_of_person == first->name) {
		
		Employee* temp = first;

		for (size_t i = 0; i < this->allEmployees.size(); i++) {

			if (allEmployees[i] == temp) {
				allEmployees.erase(allEmployees.begin(), allEmployees.begin() + i);
			}

		}

		if (first->employee_count == 0) {
			if (first->boss->employee_count == 1) {
				first->boss->employee = nullptr;
			}
			else {
				Employee* tmp = first->boss->employee;
				if (tmp == first) {
					first = first->colleague;
				}
				else {

					while (tmp->colleague != first) {
						tmp = tmp->colleague;
					}
					tmp->colleague = tmp->colleague->colleague;
				}
			}
		}
		else if (first->colleague != nullptr) {

			Employee* tmp = first->colleague;
			while (tmp->colleague != nullptr) {
				tmp = tmp->colleague;
			}
			tmp->colleague = first->employee;
			Employee* tem = first->employee;
			while (tem != nullptr) {
				tem->boss = first->boss;
				tem = tem->colleague;
			}

			if (first->boss->employee == first){
				first->boss->employee = first->colleague;
			}
			else {
				Employee* tm = first->boss->employee;
				while (tm->colleague != first) {
					tm = tm->colleague;
				}
				tm->colleague = first->colleague;
			}
			
		}
		else {
			first->boss->employee = first->employee;
			first = first->employee;
			Employee* tmp = first;
			while (tmp != nullptr) {
				tmp->boss = temp->boss;
				tmp = tmp->colleague;
			}
			

		}

		this->size--;
		return true;

	}

	else {
		return fire(name_of_person, first->colleague) || fire(name_of_person, first->employee);
	}
}

size_t Tree::height(const Employee* first)const {

	if (!first) {
		return 0;
	}
	return std::max(1 + height(first->employee), height(first->colleague));
}

//call with person->employee
void Tree::count_descendants(const Employee* person, int& counter)const {
	if (!person) {
		return;
	}
	count_descendants(person->employee,counter);
	counter++;
	count_descendants(person->colleague, counter);
	return;
}

void Tree::count_overloaded(int n, const Employee* first, int& count)const{

	if (!first) {
		return;
	}
	int counter = 0;
	count_descendants(first->employee, counter);
	
	if (counter > n) {
		count++;
	}
	
	count_overloaded(n, first->employee, count);
	count_overloaded(n, first->colleague, count);
}

unsigned long Tree::paycheck(const Employee* person, const Employee* first)const {

	if (!find(person->name, first)) {
		return 0;
	}
	int counter = 0;
	count_descendants(person->employee, counter);
	size_t descendants = counter;
	descendants -= person->employee_count;
	unsigned long payment = 500 * person->employee_count;
	payment += (50 * descendants);

	return payment;
}

string Tree::printTree(const Employee* first)const {

	vector<string> pairs;

	fillPairs(first, &pairs);
	sortPairs(&pairs);

	string toReturn;
	for (size_t i = 0; i < pairs.size(); i++) {

		toReturn += pairs[i] + '\n';

	}

	return toReturn;
}

bool Tree::InQueue(std::queue<const Employee*> q, Employee* el)const {

	while (!q.empty()) {

		const Employee* temp = q.front();
		q.pop();
		if (temp == el) {
			return true;
		}

	}
	return false;
}

bool Tree::InTree(string el)const {

	for (size_t i = 0; i < this->allEmployees.size(); i++) {

		if (allEmployees[i]->name == el) {
			return true;
		}

	}
	return false;
}

void Tree::sortPairs(vector<string>* pars)const {

	vector<string> pairs = *pars;

	for (size_t i = 0; i < pairs.size(); i++) {

		for (size_t j = 0; j < pairs.size()-1; j++) {

			std::vector<string> first_pair;
			std::vector<string> second_pair;
			std::string str;
			for (size_t k = 0; k < pairs[j].size(); k++) {

				if (pairs[j][k] != '-') {
					str.push_back(pairs[j][k]);
				}
				else {
					first_pair.push_back(str);
					str.clear();
				}
				if (k == pairs[j].size() - 1) {
					first_pair.push_back(str);
					str.clear();
				}
			}

			for (size_t k = 0; k < pairs[j+1].size(); k++) {

				if (pairs[j+1][k] != '-') {
					str.push_back(pairs[j+1][k]);
				}
				else {
					second_pair.push_back(str);
					str.clear();
				}
				if (k == pairs[j+1].size() - 1) {
					second_pair.push_back(str);
					str.clear();
				}

			}
			if (first_pair[0] == second_pair[0]) {
				
				if (first_pair[1] > second_pair[1]) {
					std::swap(pairs[j], pairs[j + 1]);
				}

			}

		}

	}
	pars = &pairs;
}

void Tree::fillPairs(const Employee* first, vector<string>* pairs)const {

	if (!first) {
		return;
	}

	std::queue<const Employee*> q;

	q.push(first);

	while (!q.empty()) {
		const Employee* temp = q.front();
		q.pop();

		if (temp->boss) {
			pairs->push_back(temp->boss->name + '-' + temp->name);
		}
		
		if (temp->colleague) {
			Employee* tm = temp->colleague;
			while (tm != nullptr) {
				if (!InQueue(q, tm)) {
					q.push(tm);
				}
				tm = tm->colleague;
			}
		}

		if (temp->employee) {
			Employee* tm = temp->employee;
			while(tm != nullptr){
				if (!InQueue(q, tm)) {
					q.push(tm);
				}
				tm = tm->colleague;
			}
		}

	}

	
}

Employee* Tree::curEmployee(string name, Employee* first) {


	if (!first) {
		return nullptr;
	}

	if (first->name == name) {
		return first;
	}

	Employee* temp = curEmployee(name, first->colleague);
	Employee* tm = curEmployee(name, first->employee);
	if (temp != nullptr && temp->name == name) {
		return temp;
	}
	else if (tm!= nullptr && tm->name == name) {
		return tm;
	}
}

const Employee* Tree::curEmployee(string name, const Employee* first)const {

	if (!first) {
		return nullptr;
	}

	if (first->name == name) {
		return first;
	}

	const Employee* temp = curEmployee(name, first->colleague);
	const Employee* tm = curEmployee(name, first->employee);
	if (temp != nullptr && temp->name == name) {
		return temp;
	}
	else if (tm != nullptr && tm->name == name) {
		return tm;
	}
}

bool Tree::isEmployee(const Employee* person, const Employee* boss)const {

	Employee* emp = boss->employee;
	while (emp != nullptr) {

		if (emp == person) {
			return true;
		}
		emp = emp->colleague;

	}
	return false;
}

//finish later
void Tree::merge(const Tree* other, const Employee* other_first, const Employee* first, Tree& merged, Employee* merged_first, bool& exit_rec)const {

	if (exit_rec) {
		return;
	}
	if (!first) {
		return;
	}
	if (first->name != "Uspeshnia") {
		if (InTree(first->name) && other->InTree(first->name)) {

			const Employee* inOther = other->curEmployee(first->name, other_first);
			const Employee* bossOther = other->curEmployee(inOther->boss->name, other_first);

			if (other->isEmployee(bossOther, inOther)) {
				exit_rec = 1;
				return;
			}

			Employee* person = new Employee(first->name);
			Employee* bossInMerged;
			if (inOther->boss->name == first->boss->name) {
				bossInMerged = merged.curEmployee(first->boss->name, merged_first);
			}
			else {
				if (first->boss->level < inOther->boss->level) {

					bossInMerged = merged.curEmployee(first->boss->name, merged_first);

				}
				else if (first->boss->level > inOther->boss->level) {

					bossInMerged = merged.curEmployee(inOther->boss->name, merged_first);

				}
				else {
					if (first->boss->name < inOther->boss->name) {

						bossInMerged = merged.curEmployee(first->boss->name, merged_first);

					}
					else {

						bossInMerged = merged.curEmployee(inOther->boss->name, merged_first);

					}
				}
			}
			merged.insert(person, bossInMerged, merged_first, 1);

		}
		else if (InTree(first->name) && !other->InTree(first->name)) {

			Employee* bossInMerged = merged.curEmployee(first->boss->name, merged_first);
			Employee* person = new Employee(first->name);
			merged.insert(person, bossInMerged, merged_first, 1);

		}
		
	}
	merge(other, other_first, first->colleague, merged, merged_first, exit_rec);
	merge(other, other_first, first->employee, merged, merged_first, exit_rec);
	
}

void Tree::fillRestOfOther(Tree& merged, Employee* merged_first, const Employee* first)const {

	if (!first) {
		return;
	}

	if (!merged.InTree(first->name)) {
		Employee* bossInMerged = merged.curEmployee(first->boss->name, merged_first);
		Employee* person = new Employee(first->name);
		merged.insert(person, bossInMerged, merged_first, 1);
	}

	fillRestOfOther(merged, merged_first, first->colleague);
	fillRestOfOther(merged, merged_first, first->employee);

}

