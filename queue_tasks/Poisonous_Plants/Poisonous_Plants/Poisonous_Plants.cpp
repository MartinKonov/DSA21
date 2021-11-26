#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int poisonousPlants(vector<int> p) {

	if (p.empty()) {
		return 0;
	}

	int days_passed = 0;

	queue<int> plants, survivors;


	int sz_vec = p.size();
	for (int i = 0; i < sz_vec; i++) {
		plants.push(p[i]);
	}

	int last_front;
	while (true) {
		
		queue<int> cpy_of_plants = plants;

		last_front = plants.front();

		survivors.push(plants.front());
		plants.pop();

		while (!plants.empty()) {

			if (plants.front() > last_front) {
				last_front = plants.front();
				plants.pop();
			}
			else {
				last_front = plants.front();
				survivors.push(plants.front());
				plants.pop();
			}
		}

		plants = survivors;
		
		if (cpy_of_plants == plants) {
			break;
		}

		while (!survivors.empty()) {
			survivors.pop();
		}

		days_passed++;

	}


	return days_passed;
}


int main() {

	vector<int> p = { 1, 5, 4, 3, 2 };


	//6 7 8
	cout << poisonousPlants(p);

}