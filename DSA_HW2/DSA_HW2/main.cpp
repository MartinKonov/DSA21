#include<fstream>
#include<iostream>
#include"interface.h"
#include"cmdHandler.h";

//Tests.cpp and main.cpp are in the same file due to technical issues with my compiler.

size_t strSize(string str) {

	size_t counter = 0;

	char letter = str[0];
	counter++;
	while (letter != '\0') {
		letter = str[counter];
		counter;
	}
	return counter;
}

vector<string> unpack_command(string cmd, size_t size) {
	vector<string> ToReturn;
	string word;
	for (size_t i = 0; i < size; i++) {

		if (cmd[i] != ' ') {
			word += cmd[i];
		}
		else {
			ToReturn.push_back(word);
			word.clear();
		}
	}

	return ToReturn;
}


bool exists(string obj_name, vector<Hierarchy*> objects) {

	for (size_t i = 0; i < objects.size(); i++) {

		if (objects[i]->name == obj_name) {
			return true;
		}

	}
	return false;
}

void handleHelp() {

	std::cout << "\n\"load\" \"name_of_object\" \"name_of_file\"(optional):" << std::endl;
	std::cout << "If given \"name_of_file\", loads a hierarchy with name \"name_of_object\" from the given file.\n If \"name_of_file\" is missing, then creates a new hierarchy with the given \"name_of_object\". Then you can input the data you need to be loaded from the console.\n When you are done with your input, press \"ctrl + z\" or \"ctrl + d\"\n";
	std::cout << "\n\"save\" \"name_of_object\" \"name_of_file\":" << std::endl;
	std::cout << "Saves the given object in the given file. If the file name is missing, then prints the hierarchy on the screen\n";
	std::cout << "\n\"find\" \"name_of_object\" \"name_of_employee\":" << std::endl;
	std::cout << "Finds if the given employee is present in the given object.\n";
	std::cout << "\n\"num_subordinates\" \"name_of_object\" \"name_of_employee\":" << std::endl;
	std::cout << "Shows the count of immidiate employees of \"name_of_employee\" in the given object\n";
	std::cout << "\n\"manager\" \"name_of_object\" \"name_of_employee\":" << std::endl;
	std::cout << "Shows the name of the manager of the given employee in the given hierarchy.\n";
	std::cout << "\n\"num_employeea\" \"name_of_object\":" << std::endl;
	std::cout << "Shows the number of employees in the given object (hierarchy).\n";
	std::cout << "\n\"overloaded\" \"name_of_objeect\":" << std::endl;
	std::cout << "Shows the number of workers, whose employee count is greater than 20.\n";
	std::cout << "\n\"join\" \"name_of_object_1\" \"name_of_object_2\" \"name_of_result_object\":" << std::endl;
	std::cout << "Joins the first and the second object and creates a third hierarchy with the name \"name_of_result_object\".\n";
	std::cout << "\n\"fire\" \"name_of_object\" \"name_of_person\":" << std::endl;
	std::cout << "Removes the given person from the given object.\n";
	std::cout << "\n\"hire\" \"name_of_object\" \"name_of_person\" \"name_of_manager\":" << std::endl;
	std::cout << "Inserts the given person as an employee of the given manager in the given object\n";
	std::cout << "\n\"salary\" \"name_of_object\" \"name_of_person\":" << std::endl;
	std::cout << "Shows the salary of the given person in the given object\n";
	std::cout << "\n\"incorporate\" \"name_of_object\":" << std::endl;
	std::cout << "Incorporates the firm, represented by the given object\n";
	std::cout << "\n\"modernize\" \"name_of_object\":" << std::endl;
	std::cout << "Modernizes the firm, represented by the given object\n";
	std::cout << "\n\"exit\":" << std::endl;
	std::cout << "Exits the program.\n";


}

void handleload(string name_of_object, string name_of_file, vector<Hierarchy*>& objects) {

	std::ifstream file(name_of_file);
	if (file.fail()) {
		throw std::exception("File with the given name failed to open.Try again!\n");
	}
	string cmd;
	string fullData;
	while (getline(file, cmd))
	{
		fullData += cmd;
		fullData += '\n';

	}
	file.close();

	Hierarchy* loaded = new Hierarchy(fullData);
	loaded->name = name_of_object;
	objects.push_back(loaded);
	std::cout << name_of_object << " loaded successfully!\n";
}

void hadndleload(string name_of_object, vector<Hierarchy*>& objects) {

	string data, result;

	while (!getline(std::cin, data).eof()) {
		result += data + '\n';
	}
	std::cin.clear();

	try {
		Hierarchy* loaded = new Hierarchy(result);
		loaded->name = name_of_object;
		objects.push_back(loaded);
	}
	catch (std::invalid_argument& e) {
		throw std::invalid_argument(e.what());
	}
	std::cout << name_of_object << " loaded successfully!\n";
	
}

Hierarchy* curHierarchy(vector<Hierarchy*>& objects, string objname) {

	for (size_t i = 0; i < objects.size(); i++) {

		if (objects[i]->name == objname) {
			return objects[i];
		}

	}


}

void handleSave(string obj_name, string filename, vector<Hierarchy*>& objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	std::ofstream file(filename);
	if (file.fail()) {
		throw std::exception("File save has failed. Try again!\n");
	}
	
	Hierarchy* cur = curHierarchy(objects, obj_name);

	string ToSave = cur->print();
	file << ToSave;
	std::cout << obj_name << " saved!\n";
}

void handleSave(string obj_name, vector<Hierarchy*>& objects) {

	if (!exists(obj_name, objects))	{

		throw std::invalid_argument("Object");

	}
	Hierarchy* obj = curHierarchy(objects, obj_name);

	std::cout << obj->print();

}

void handleFind(string obj_name, string employee, vector<Hierarchy*> objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);
	if (obj->find(employee)) {
		std::cout << employee << " is employed in " << obj_name << ".\n";
	}
	else {
		std::cout << employee << " is not employed in " << obj_name << ".\n";
	}

}

void handleNumSub(string obj_name, string employee, vector<Hierarchy*> objects) {
	
	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}
	
	Hierarchy* obj = curHierarchy(objects, obj_name);

	if (!obj->find(employee)) {
		throw std::invalid_argument("Employee");
	}

	int sub = obj->num_subordinates(employee);

	if (!sub) {
		std::cout << employee << " has no subordinates.\n";
	}
	else {
		std::cout << employee << " has " << sub << " subordinates.\n";
	}

}

void handleManager(string obj_name, string employee, vector<Hierarchy*> objects) {
	
	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	if (!obj->find(employee)) {
throw std::invalid_argument("Employee");
	}

	string manager = obj->manager(employee);

	std::cout << "Manager of " << employee << " is " << manager << "." << std::endl;

}

void handleNumEmployees(string obj_name, vector<Hierarchy*> objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	int num = obj->num_employees();

	std::cout << obj_name << " has " << num << " employees.\n";
}

void handleOverloaded(string obj_name, vector<Hierarchy*> objects) {

	if (!exists(obj_name, objects)) {

		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	int num = obj->num_overloaded();

	if (!num) {
		std::cout << obj_name << " has no overloaded employees.\n";
	}
	else {
		std::cout << obj_name << " has " << num << " overloaded employees.\n";
	}

}

void handleJoin(string first_obj_name, string second_obj_name, string result_obj_name, vector<Hierarchy*>& objects) {

	if (!exists(first_obj_name, objects) || !exists(second_obj_name, objects)) {

		throw std::invalid_argument("Object/s with the given name doesn't exits");

	}
	Hierarchy* first_obj = curHierarchy(objects, first_obj_name);
	Hierarchy* second_obj = curHierarchy(objects, second_obj_name);

	Hierarchy result_h = first_obj->join(*second_obj);
	string data = result_h.print();
	Hierarchy* res = new Hierarchy(data);
	if (first_obj->tree.size > 0 || second_obj->tree.size > 0) {
		if (res->tree.size == 0) {
			delete res;
			throw std::invalid_argument("Join has failed");
		}
	}
	
	res->name = result_obj_name;
	objects.push_back(res);
	
	std::cout << result_obj_name << " created!\n";
	
}

void handleFire(string obj_name, string employee, vector<Hierarchy*> objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("obj_name");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	if (!obj->find(employee)) {
		throw std::invalid_argument("employee");
	}

	obj->fire(employee);

	std::cout << employee << " was fired.\n";
}

void handlehire(string obj_name, string employee, string manager, vector<Hierarchy*>& objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	if (!obj->find(manager)) {
		throw std::invalid_argument("Manager");
	}

	obj->hire(employee, manager);

	std::cout << employee << " was hired.\n";

}

void handleSalary(string obj_name, string employee, vector<Hierarchy*>& objects){

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	if (!obj->find(employee)) {
		throw std::invalid_argument("Employee");
	}

	std::cout <<"The salary is "<<obj->getSalary(employee) << " BGN.\n";
	
}

void handleIncorporate(string obj_name, vector<Hierarchy*>& objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	obj->incorporate();

	std::cout << obj_name << " was incorporated.\n";
}

void handleModernize(string obj_name, vector<Hierarchy*>& objects) {

	if (!exists(obj_name, objects)) {
		throw std::invalid_argument("Object");
	}

	Hierarchy* obj = curHierarchy(objects, obj_name);

	obj->modernize();

	std::cout << obj_name << " was modernized\n";
}

void delData(vector<Hierarchy*>& objects) {

	for (size_t i = 0; i < objects.size(); i++) {

		delete objects[i];

	}

}

int main() {

	char command[2000];
	std::cout << "Enter a command to start the program!\n For list of commands, type \"help\".\n";
	vector<Hierarchy*> objects;
	std::cin.getline(command, 2000);

	while (strcmp(command, "exit")) {
		
		CmdHandler cmd(command);

		if (cmd.getMainCmd() == "help") {
			handleHelp();
			std::cin.getline(command, 2000);
			continue;
		}
		else if (cmd.getMainCmd() == "load") {
			if (cmd.split_command.size() == 3) {
				try {
					handleload(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch (std::exception& e) {
					std::cout << e.what();
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else if (cmd.split_command.size() == 2) {
				try {
					hadndleload(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what();
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "save") {
			if (cmd.split_command.size() == 3) {
				try {
					handleSave(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesnt exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
				catch (std::exception& e) {
					std::cout << e.what();
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else if (cmd.split_command.size() == 2) {
				try {
					handleSave(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesnt exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "find") {

			if (cmd.split_command.size() == 3) {
				try {
					handleFind(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() <<" with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
		}
		}
		else if (cmd.getMainCmd() == "num_subordinates") {
			if (cmd.split_command.size() == 3) {
				try {
					handleNumSub(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch(std::invalid_argument& e){
					std::cout << e.what() <<" with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "manager") {
		
			if (cmd.split_command.size() == 3) {
				try {
					handleManager(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() <<" with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "num_employees") {
			if (cmd.split_command.size() == 2) {
				try {
					handleNumEmployees(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "overloaded") {
			if (cmd.split_command.size() == 2) {
				try {
					handleOverloaded(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() <<" with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "join") {
			if (cmd.split_command.size() == 4) {
				try {
					handleJoin(cmd.split_command[1], cmd.split_command[2], cmd.split_command[3], objects);

				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " .Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.split_command[0] == "fire") {
			
			if (cmd.split_command.size() == 3) {
				try {
					handleFire(cmd.split_command[1],cmd.split_command[2], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "hire") {
		if (cmd.split_command.size() == 4) {
			try {
				handlehire(cmd.split_command[1], cmd.split_command[2], cmd.split_command[3], objects);
			}
			catch (std::invalid_argument &e) {
				std::cout << e.what() <<" with the given name doesn't exist. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else {
			std::cout << "Invalid input. Try again!\n";
			std::cin.getline(command, 2000);
			continue;
		}
		}
		else if (cmd.getMainCmd() == "salary") {
			if (cmd.split_command.size() == 3) {

				try {
					handleSalary(cmd.split_command[1], cmd.split_command[2], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}

			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "incorporate") {
			if(cmd.split_command.size() == 2) {
				try {
					handleIncorporate(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else if (cmd.getMainCmd() == "modernize") {
			if (cmd.split_command.size() == 2) {
				try {
					handleModernize(cmd.split_command[1], objects);
				}
				catch (std::invalid_argument& e) {
					std::cout << e.what() << " with the given name doesn't exist. Try again!\n";
					std::cin.getline(command, 2000);
					continue;
				}
			}
			else {
				std::cout << "Invalid input. Try again!\n";
				std::cin.getline(command, 2000);
				continue;
			}
		}
		else {
			std::cout << "Invalid command. For more information about the commands, type \"help\" and press \"Enter\".\n";
		}

		std::cin.getline(command, 2000);
	}


	delData(objects);
}