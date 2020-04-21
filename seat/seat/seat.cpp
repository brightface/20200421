#include <iostream>

using namespace std;

int arr[1010][1010];
int num = 1;
int direction = 1;


int main() {
	int r, c, wait;
	cin >> r >> c >> wait;
	int i = -1;
	int j = 0;
	int flag1 = 0;
	int flag2 = 0;
	int k = 0;
	while (1) {
		if (r > 0) {
			for (int p = 0; p < r; p++) {
				i = i + direction;
				arr[i][j] = num;
				num++;
				k++;
				if (k == wait) {
					cout << i+1 << " " << j+1;
					return 0;
				}
			}
		}
		c--;
		if (c < 0 && r < 0) break;
		if (c > 0) {
			for (int p = 0; p < c; p++) {
				j = j + direction;
				arr[i][j] = num;
				num++;
				k++;
				if (k == wait) {
					cout << i+1 << " " << j+1;
					return 0;
				}
			}
		}
		r--;
		direction = -(direction);
		if (c <= 0 && r <= 0) break;
	}

	/*for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (k == arr[i][j]) {
				cout << i << " " << j;
				return 0;
			}
		}
	}*/
}