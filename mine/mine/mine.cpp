#include<iostream>
using namespace std;

int map[110][110];
int main() {
	int cnt = 0;
	int map_x, map_y, mine_x, mine_y;
	cin >> map_y >> map_x >> mine_y >> mine_x;

	//input
	for (int i = 2; i < map_y + 2; i++) {
		for (int j = 2; j < map_x + 2; j++) {
			cin >> map[i][j];
		}
	}
	//입력 받을때만 하면 된다. 정수로 받으면 0 부터 되서 굳이 할필요 없어
	//output 4 6
	if (map[mine_y + 1][mine_x + 1] == 1) {
		cout << "game over";
	}
	else
	{
		if (map[mine_y][mine_x] == 1) cnt++;
		if (map[mine_y + 1][mine_x] == 1) cnt++;
		if (map[mine_y + 2][mine_x] == 1) cnt++;
		if (map[mine_y + 2][mine_x + 1] == 1) cnt++;
		if (map[mine_y + 2][mine_x + 2] == 1) cnt++;
		if (map[mine_y + 1][mine_x + 2] == 1) cnt++;
		if (map[mine_y][mine_x + 2] == 1) cnt++;
		if (map[mine_y][mine_x + 1] == 1) cnt++;

		cout << cnt;
	}
	return 0;
}