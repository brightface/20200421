#include <iostream>
using namespace std;
int arr[1000];
int cnt[10];
int max;
int main() {
	int n;
	cin >> n;

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < 5; i++) {
			cin >> arr[i];
			cnt[arr[i]]++;
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