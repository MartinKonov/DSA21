#pragma once
#include<string>
#include<vector>

using std::string;
using std::vector;
using std::size_t;


class CmdHandler {
	string starting_command;
	string main_command;
public:
	vector <string> split_command;

	CmdHandler(string start_cmd) {
		this->starting_command = start_cmd;
	
		string temp;
		for (size_t i = 0; i < this->starting_command.size(); i++) {

			if (starting_command[i] != ' ') {
				temp.push_back(this->starting_command[i]);
			}
			else {
				this->split_command.push_back(temp);
				temp.clear();
			}

		}
		this->split_command.push_back(temp);


		this->main_command = this->split_command[0];
	}

	string getMainCmd() {
		return this->main_command;
	}


};