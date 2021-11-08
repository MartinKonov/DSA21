#include<iostream>
#include<stack>

using std::stack;
using std::size_t;
using std::string;

using std::cin;
using std::cout;
using std::endl;

string taskOne(string input) {

	stack<char> something;
	for (int i = 0;  i < input.size(); i++) {
		something.push(input[i]);
	}
	size_t sthSize = something.size();

	for (int i = 0; i < sthSize; i++) {
		input[i] = (something.top());
		something.pop();
	}
	return input;
}




void sortStack(stack<int>& firstStack) {

	stack<int> result;

	int helperOne = -1;
	int helperTwo = -1;

	int lowest = 999999;

	int size = firstStack.size();

	while (result.size() != size) {
		stack<int> CurrentResOne;

		int sz = firstStack.size();

		for (int i = 0; i < sz; i++) {
			if (firstStack.top() < lowest) {
				if (i != 0) {
					if (helperOne < 0) {
						helperOne = lowest;
					}
					else if (helperTwo < 0) {
						helperTwo = lowest;
					}
					else {
						if (helperOne >= helperTwo) {
							CurrentResOne.push(helperTwo);
							helperTwo = lowest;
						}
						else if (helperOne <= helperTwo) {
							CurrentResOne.push(helperOne);
							helperOne = lowest;
						}

					}
				}
				lowest = firstStack.top();
				firstStack.pop();
			}
			else {
				if (helperOne < 0) {
					helperOne = firstStack.top();
					firstStack.pop();
				}
				else if (helperTwo < 0) {
					helperTwo = firstStack.top();
					firstStack.pop();
				}
				else {
					if (helperOne >= helperTwo) {
						CurrentResOne.push(helperTwo);
						helperTwo = firstStack.top();
						firstStack.pop();
					}
					else if (helperOne <= helperTwo) {
						CurrentResOne.push(helperOne);
						helperOne = firstStack.top();
						firstStack.pop();
					}
				}
			}
		}
		if (helperOne > -1) {
			CurrentResOne.push(helperOne);
			helperOne = -1;
		}
		if (helperTwo > -1) {
			CurrentResOne.push(helperTwo);
			helperTwo = -1;
		}
		result.push(lowest);
		lowest = 9999999;
		firstStack = CurrentResOne;
	}

	int resSize = result.size();
	for (int i = 0; i < resSize; i++) {
		cout << result.top() << endl;
		result.pop();
	}
}




int main() {

	stack<int> StackToSort;
	StackToSort.push(1);
	StackToSort.push(3);
	StackToSort.push(6);
	StackToSort.push(2);
	StackToSort.push(5);
	StackToSort.push(4);
	sortStack(StackToSort);
}