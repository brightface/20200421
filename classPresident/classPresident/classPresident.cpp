#include <iostream>
using namespace std;
int arr[1000][1000];
int cnt[10];
int max;
int main() {
	int n;
	cin >> n;
	//row is student, col is grade
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> arr[i][j];
		}
	}

	//선택정렬
	for (int w = 0; w < 5; w++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (arr[j][w] == arr[k][w]) {
					cnt[arr[j][w]]++;
				}

			}
		}
	}

	// max=cnt[0];
	for (int i = 1; i < 10; i++) {
		if (cnt[i] > max) {
			if (cnt[i] == max) {
				continue;
			}
			else max = cnt[i];
		}
	}
	cout << max;

	//Please Enter Your Code Here

	return 0;
}