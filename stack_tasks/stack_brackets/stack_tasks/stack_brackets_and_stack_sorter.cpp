#include <iostream>
#include<vector>
#include <stack>

using std::vector;
using std::size_t;
using std::stack;
using std::string;

using std::cin;
using std::cout;
using std::endl;



bool bracketsValidator(string input) {

	stack<char> brackets;


	for (int i = 0; i < input.size(); i++) {

		if (input[i] != '(' && input[i] != '[' && input[i] != '{' && input[i] != ')' && input[i] != ']' && input[i] != '}') {
			continue;
		}


		if ((input[i] == ')' || input[i] == ']' || input[i] == '}') && brackets.empty()) {
			return false;
		}

		if (input[i] == '(' || input[i] == '[' || input[i] == '{') {
			brackets.push(input[i]);
		}
		if ((input[i] == ')' && brackets.top() == '(') || (input[i] == ']' && brackets.top() == '[') || (input[i] == '}'
			&& brackets.top() == '{')) {

			brackets.pop();

		}

	}
	if (brackets.size() == 0) {
		return true;
	}
	return false;


}

int main()
{
	string input;
	cin >> input;
	
	cout << bracketsValidator(input);


}


