#include <iostream>
using namespace std;

int arr[100][5];
int president[100];
int main() {
	int grade = 5;
	int student;
	cin >> student;
	int flag = 0;

	for (int i = 0; i < student; i++) {
		for (int j = 0; j < grade; j++) {
			cin >> arr[i][j];
		}
	}

	for (int j = 0; j < grade; j++) {
		for (int k = 0; k < student; k++) {
			for (int i = 1; i < student; i++) {
				if (flag >= 1) { i += flag; }
				if (arr[k][j] == arr[i][j]) {
					president[i]++;
					president[k]++;
				}
			}
			flag = flag + 1;
		}flag = 0;
	}

	int max = president[0];
	int tmp = 0;
	int ans = 0;
	for (int i = 0; i < student; i++) {
		if (president[i] > max) {
			max = president[i];
			ans = i+1;
		}
		else if (max == president[i]) {
			continue;
		}
	}
	cout << ans;
}