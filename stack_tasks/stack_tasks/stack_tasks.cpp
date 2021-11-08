#include<iostream>
#include<stack>

using std::stack;
using std::size_t;
using std::string;

using std::cin;
using std::cout;
using std::endl;

void sortStack(stack<int>& firstStack) {

	stack<int> result;
	int lowest = 999999;
	int size = firstStack.size();

	while (result.size() != size) {
		stack<int> CurrentResOne;

		int sz = firstStack.size();

		for (int i = 0; i < sz; i++) {
			if (firstStack.top() < lowest) {
				CurrentResOne.push(lowest);
				lowest = firstStack.top();
				firstStack.pop();
			}
			else {
				CurrentResOne.push(firstStack.top());
				firstStack.pop();
			}
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
	StackToSort.push(123);
	StackToSort.push(2);
	StackToSort.push(55);
	StackToSort.push(-4);
	sortStack(StackToSort);
}