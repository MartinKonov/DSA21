#include<iostream>
#include<stack>
#include<queue>

using std::pair;
using std::string;
using std::queue;


enum Terrain
{
	TAKEN = 1,
	START = 2,
	FREE = 0,
	FINAL = 9
};



const int Xdirections[4] = { 0, 1, 0, -1 };
const int Ydirections[4] = { 1, 0, -1, 0 };



template<typename T>
void print_map(T map[8][10]) {


	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 10; j++) {
			std::cout << map[i][j];

		}
		std::cout << '\n';
	}

}

bool isSafe(int map[8][10], int first, int second) {

	if (first < 0 || first >= 8 || second < 0 || second >= 10 || map[first][second] == TAKEN || map[first][second] == '^' || map[first][second] == 'v' ||
		map[first][second] == '<' || map[first][second] == '>') {
		return false;
	}
	return true;
}

void findShortestPath(int map[8][10]) {

	queue<pair<int, int>> path;
	path.push({ 0,0 });
	char mapCpy[10][10];


	while (!path.empty()) {

		pair<int, int> current = path.front();
		path.pop();

		for (size_t i = 0; i < 4; i++) {

			if (isSafe(map, current.first + Xdirections[i], current.second + Ydirections[i])) {
				pair<int, int> newPair;
				newPair.first = current.first + Xdirections[i];
				newPair.second = current.second + Ydirections[i];
				path.push(newPair);

				if (Xdirections[i] == 0 && Ydirections[i] == 1) {
					map[newPair.first][newPair.second] = '<';
					mapCpy[newPair.first][newPair.second] = '<';
					
				}
				else if (Xdirections[i] == 1 && Ydirections[i] == 0) {
					map[newPair.first][newPair.second] = '^';
					mapCpy[newPair.first][newPair.second] = '^';
					
				}
				else if (Xdirections[i] == -1 && Ydirections[i] == 0) {
					map[newPair.first][newPair.second] = 'v';
					mapCpy[newPair.first][newPair.second] = 'v';
					
				}
				else if(Xdirections[i] == 0 && Ydirections[i] == -1){
					map[newPair.first][newPair.second] = '>';
					mapCpy[newPair.first][newPair.second] = '>';
				}
			}
		}
	}
	std::cout << '\n';
	print_map(mapCpy);


}


int main() {


	int map[8][10] = {	
		{ START , TAKEN , FREE , FREE  , FREE , FREE  , FREE , TAKEN , FREE , FREE },
		{ FREE , TAKEN , FREE , FREE  , FREE , FREE  , FREE , TAKEN , FREE , FREE },
		{ FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE },
		{ FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
		{ FREE , TAKEN , FREE , FREE  , FREE , TAKEN , FREE , FREE  , FREE , FREE },
		{ FREE , FREE  , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
		{ FREE , TAKEN , FREE , TAKEN , FREE , TAKEN , FREE , FREE  , FREE , FREE },
		{ FREE , TAKEN , FREE , FREE  , FREE , TAKEN , FREE , FREE  , FREE , FINAL },	
	};


	//print_map(map);
	findShortestPath(map);




	
	
	


}