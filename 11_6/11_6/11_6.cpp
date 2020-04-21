#include <iostream>
#include <vector>
//뒤집기
//3중포문
//sum 의 n의개수로 면적찾기
using namespace std;
int map[1000][1000];
int cnt[100];

int main() {
	int n;
	int paper = 1;
	cin >> n;
	int x, y, width, height;
	for (paper = 1; paper < n + 1; paper++) {
		cin >> x >> y >> width >> height;
		// }

		// for (int j=0;j<n;j++){
		for (int i = x; i < x+width; i++) {
			for (int j = y; j < y+height; j++) {
				map[i][j] = paper;
			}
		}
		
	}

	for (int k = 1; k < n + 1; k++) {
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				if (map[i][j] == k) {
					cnt[k]++;
				}
			}
		}
	}
	for (int w = 1; w < n+1; w++) {
		cout << cnt[w] << endl;
	}
	return 0;
}