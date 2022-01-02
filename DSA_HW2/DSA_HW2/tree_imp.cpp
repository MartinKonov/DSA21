#include"tree.h"

Tree::Tree() {
	this->size = 0;
}

Tree::~Tree() {
	this->allEmployees.clear();
}

void Tree::deltree(Employee*& first) {

	if (first != nullptr) {

		deltree(first->employee);
		deltree(first->colleague);
		delete first;
		first = nullptr;
		this->size--;
	}
	int a = 5;
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

bool Tree::insert(string person_name, string boss, Employee* first) {

	if (!first) {
		return false;
	}

	Employee* bos = curEmployee(boss, first);
	if (InTree(person_name)) {
		Employee* human = curEmployee(person_name, first);
		if (human->boss == bos) {
			return true;
		}
		else {
			if (human->boss->employee_count == 1) {
				human->boss->employee_count--;
				human->boss->employee = nullptr;
			}
			else {
				if (human->boss->employee == human) {
					human->boss->employee = human->colleague;
					human->boss->employee_count--;
				}
				else {
					Employee* temp = human->boss->employee;
					while (temp->colleague != human) {
						temp = temp->colleague;
					}
					temp->colleague = temp->colleague->colleague;
					human->boss->employee_count--;
				}

			}

			human->boss = bos;
			if (bos->employee_count == 0) {
				bos->employee = human;
				bos->employee_count++;
			}
			else {
				Employee* temp = bos->employee;
				while (temp->colleague != nullptr) {
					temp = temp->colleague;
				}
				temp->colleague = human;

			}
			human->colleague = nullptr;
			human->level = human->boss->level + 1;
			incLevels(human->employee);
		}
	}

	if (first->name == boss) {

		if (bos->employee_count == 0) {
			bos->employee_count++;
			Employee* person = new Employee(person_name, bos, nullptr, nullptr);
			bos->employee = person;
			person->level = bos->level + 1;
			this->allEmployees.push_back(person);
		}
		else {
			Employee* temp = bos->employee;
			while (temp->colleague != nullptr) {
				temp = temp->colleague;
			}
			Employee* person = new Employee(person_name, bos, nullptr, nullptr);
			temp->colleague = person;
			bos->employee_count++;
			person->level = bos->level + 1;
			this->allEmployees.push_back(person);
		}
		this->size++;
		return true;
	}

	return insert(person_name, boss, first->colleague) || insert(person_name, boss, first->employee);

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

	if (!find(name_of_person, first) || name_of_person == "Uspeshnia") {
		return 0;
	}

	Employee* person = curEmployee(name_of_person, first);


	for (size_t i = 0; i < this->allEmployees.size(); i++) {

		if (allEmployees[i] == person) {
			if (i == 0) {
				allEmployees.erase(allEmployees.begin(), allEmployees.begin() + 1);
			}
			else {
				allEmployees.erase(allEmployees.begin(), allEmployees.begin() + i);
			}
		}

	}

	if (person->boss->employee_count == 1) {
		if (person->employee_count == 0) {
			person->boss->employee_count = 0;
			person->boss->employee = nullptr;
			person->boss = nullptr;
			delete person;
		}
		else {
			Employee* temp = person->employee;
			person->boss->employee = temp;
			
			while (temp != nullptr) {

				temp->boss = person->boss;
				temp->level--;
				if (temp->employee) {
					incLevels(temp->employee);
				}
				person->boss->employee_count++;
				temp = temp->colleague;
			}
			person->employee = nullptr;
			person->boss->employee_count--;
			person->boss = nullptr;
			delete person;
		}
	}
	else if(person->boss->employee_count > 1){
		Employee* tmp = person->boss->employee;
		if (tmp == person) {
			person->boss->employee = person->colleague;
		}
		else {
			while (tmp != nullptr) {
				if (tmp->colleague == person) {
					tmp->colleague = tmp->colleague->colleague;
				}
				tmp = tmp->colleague;
			}
		}
		if (person->employee_count > 0) {

			Employee* temp = person->employee;
			while (temp != nullptr) {
				temp->boss = person->boss;
				Employee* tm = temp->boss->employee;
				while (tm->colleague != nullptr) {
					if (tm->colleague == temp) {
						break;
					}
					tm = tm->colleague;
				}
				tm->colleague = temp;
				temp->level--;
				incLevels(temp);
				person->boss->employee_count++;
				temp = temp->colleague;
			}
		}
		person->boss->employee_count--;
		person->boss = nullptr;
		delete person;
	}
	this->size--;

	return 1;
	
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

void Tree::delPairs(vector<pair*>& pairs)const {

	for (size_t i = 0; i < pairs.size(); i++) {
		delete pairs[i];
	}
}

string Tree::printTree(const Employee* first)const {

	vector<pair*>pairs;
	fillPairs(first, pairs);
	if (pairs.size() == 0) {
		return "";
	}
	sortPairs(pairs);

	string toReturn = fillString(pairs);
	delPairs(pairs);

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

void Tree::sortPairs(vector<pair*>& pars)const {

	for (size_t i = 0; i < pars.size() -1; i++) {
		for (size_t j = 0; j < pars.size()- i -1; j++) {

			if (pars[j]->boss->level > pars[j + 1]->boss->level) {
				std::swap(pars[j], pars[j + 1]);
			}

		}
	}

	for (size_t i = 0; i < pars.size() - 1; i++) {
		for (size_t j = 0; j < pars.size() - i - 1; j++) {

			if (pars[j]->boss->level == pars[j + 1]->boss->level) {
				if (pars[j]->boss->name == pars[j+1]->boss->name) {
					if (pars[j]->person->name > pars[j + 1]->person->name) {
						std::swap(pars[j], pars[j + 1]);
					}
				}
				else if (pars[j]->boss->name > pars[j + 1]->boss->name) {
					std::swap(pars[j], pars[j + 1]);
				}
			}

		}
	}
}

string Tree::fillString(vector<pair*>& pairs)const {

	string ToReturn;

	for (size_t i = 0; i < pairs.size(); i++) {
		ToReturn += pairs[i]->boss->name + '-' + pairs[i]->person->name;
		ToReturn += '\n';
	}
	return ToReturn;

}

void Tree::fillPairs(const Employee* first, vector<pair*>& pairs)const {

	if (!first) {
		return;
	}

	std::queue<const Employee*> q;

	q.push(first);

	while (!q.empty()) {
		const Employee* temp = q.front();
		q.pop();

		if (temp->boss) {
			pair* newPair = new pair(temp, temp->boss);
			pairs.push_back(newPair);
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

bool Tree::isEmployee(const string person, const string boss, const Employee* first)const {

	const Employee* bos = curEmployee(boss, first);
	const Employee* human = curEmployee(person, first);

	Employee* emp = bos->employee;
	while (emp != nullptr) {

		if (emp == human) {
			return true;
		}
		emp = emp->colleague;

	}
	return false;
}

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
			const Employee* bossOther = other->curEmployee(first->boss->name, other_first);

			if (other->isEmployee(bossOther->name, inOther->name, other_first)) {
				exit_rec = 1;
				return;
			}

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
					if (first->boss->name > inOther->boss->name) {

						bossInMerged = merged.curEmployee(first->boss->name, merged_first);

					}
					else {

						bossInMerged = merged.curEmployee(inOther->boss->name, merged_first);

					}
				}
			}
			merged.insert(first->name, bossInMerged->name, merged_first);

		}
		else if (InTree(first->name) && !other->InTree(first->name)) {

			merged.insert(first->name, first->boss->name, merged_first);

		}

	}
	merge(other, other_first, first->colleague, merged, merged_first, exit_rec);
	merge(other, other_first, first->employee, merged, merged_first, exit_rec);

}

void Tree::fillRestOfOther(Tree& merged, Employee* merged_first, const Employee* first)const {

	if (!first) {
		return;
	}

	if (!merged.InTree(first->name) &&  first->name != "Uspeshnia") {

		merged.insert(first->name, first->boss->name, merged_first);
	
	}

	fillRestOfOther(merged, merged_first, first->colleague);
	fillRestOfOther(merged, merged_first, first->employee);

}

void Tree::HighestPayedWorker(Employee* boss, vector<Employee*>* highest_payed_people) {

	Employee* temp = boss->employee;
	Employee* highestpaycheck = temp;
	int payment_highest = paycheck(highestpaycheck, boss);
	highest_payed_people->push_back(temp);
	temp = temp->colleague;
	while (temp != nullptr) {
		int payment_temp = paycheck(temp, boss);
		if (payment_highest < payment_temp) {
			payment_highest = payment_temp;
			highestpaycheck = temp;
			highest_payed_people->clear();
			highest_payed_people->push_back(temp);
		}
		else if (payment_highest == payment_temp) {
			highest_payed_people->push_back(temp);
		}
		temp = temp->colleague;
	}

}

void Tree::incLevels(Employee* boss_employee) {

	if (!boss_employee) {
		return;
	}

	boss_employee->level = boss_employee->boss->level + 1;

	incLevels(boss_employee->colleague);
	incLevels(boss_employee->employee);

}

void Tree::setNewBoss(Employee* temp, Employee* highestPayedEmployee) {

	while (temp != nullptr) {

		temp->boss->employee_count--;
		if (highestPayedEmployee->employee_count == 0) {

			highestPayedEmployee->employee = temp;
			highestPayedEmployee->employee_count++;
			temp->boss = highestPayedEmployee;
			temp->level = temp->boss->level + 1;
		}
		else {

			Employee* tm = highestPayedEmployee->employee;
			if (tm->colleague) {
				while (tm->colleague != nullptr) {
					tm = tm->colleague;
				}
				tm = temp;
			}
			else {
				tm->colleague = temp;
			}
			highestPayedEmployee->employee_count++;
			temp->boss = highestPayedEmployee;
		}
		temp->level = temp->boss->level + 1;
		incLevels(temp);
		temp = temp->colleague;

	}
	highestPayedEmployee->colleague = nullptr;//...
}

void Tree::incorporate(Employee* first, int& height) {


	if (!first) {
		return;
	}


	if (first->level == height) {
		if (first->boss->employee_count >= 2) {

			vector<Employee*> highestPayedPeople;
			HighestPayedWorker(first->boss, &highestPayedPeople);
			Employee* highestPayedEmployee;
			if (highestPayedPeople.size() == 1) {

				highestPayedEmployee = highestPayedPeople[0];
			}
			else {
				highestPayedEmployee = highestPayedPeople[0];
				for (int i = 0; i < highestPayedPeople.size(); i++) {
					for (int j = 0; j < highestPayedPeople.size() - 1; j++) {
						if (highestPayedEmployee->name > highestPayedPeople[j + 1]->name) {
							highestPayedEmployee = highestPayedPeople[j + 1];
						}
					}
				}

			}

			if (first->boss->employee == highestPayedEmployee) {

				Employee* temp = highestPayedEmployee->colleague;
				while (temp != nullptr) {
					setNewBoss(temp, highestPayedEmployee);
					temp = temp->colleague;
				}
				
			}
			else {
				Employee* temp = first->boss->employee;
				while (temp->colleague != highestPayedEmployee) {
					temp = temp->colleague;
				}
				temp->colleague = temp->colleague->colleague;
				Employee* tm = first->boss->employee;
				first->boss->employee = highestPayedEmployee;
				while (tm != nullptr) {
					setNewBoss(tm, highestPayedEmployee);
					tm = tm->colleague;
				}
			}


		}
	}


	incorporate(first->employee, height);
	incorporate(first->colleague, height);

}

void Tree::startincorporate(Employee* first, int& height) {

	while (true) {

		if (height > 0) {

			incorporate(first, height);
			height--;

		}
		else {
			break;
		}
	}

}

void Tree::startmodernize(Employee* first, Employee* uspeshen ,int& height) {

	bool isFired = 0;
	while (height > 0) {
		if (height % 2 != 0) {

			modernize(first, uspeshen ,height, isFired);

			if (isFired == 1) {
				height++;
				isFired = 0;
			}
		}
		height--;
	}

	incHasBeenPassed(uspeshen->employee, 0);
}

void Tree::incHasBeenPassed(Employee* boss_employee, bool inc) {

	if (!boss_employee) {
		return;
	}

	boss_employee->hasBeenPassed = inc;

	incHasBeenPassed(boss_employee->colleague, inc);
	incHasBeenPassed(boss_employee->employee, inc);
}

void Tree::modernize(Employee* first, Employee* uspeshen, int& height, bool& isFired) {

	if (!first) {
		return;
	}

	if (first->level == height) {
		if (first->employee_count > 0) {

			if (!first->hasBeenPassed) {
				incHasBeenPassed(first->employee, 1);
				fire(first->name, uspeshen);
				isFired = 1;
				return;
			}
		}
	}

	modernize(first->employee, uspeshen, height, isFired);
	modernize(first->colleague, uspeshen, height, isFired);

}


