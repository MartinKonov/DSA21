#include <iostream>
#include<queue>
using namespace std;
int main() {
	int queue_amt;
	cin >> queue_amt;
	queue<int> knights;
	for (int i = 1; i <= queue_amt; i++) {
		knights.push(i);
	}

	while (knights.size() != 1) {
		int sz = knights.size();
		queue<int>helper;
		for (int i = 1; i <= sz; i++) {

			if (i == 1 && knights.size() % 2 == 0) {
				helper.push(knights.front());
			}

			else if (i != 1 && i % 2 != 0) {
				helper.push(knights.front());
			}


			knights.pop();

		}
		knights = helper;
	}
	cout << knights.front();



}