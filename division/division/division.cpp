#include <stdio.h>
#include <iostream>
using namespace std;

int res[30];
int n, cnt;
int sum;

void division(int sum, int length) {
	if (sum == n) {
		cnt++;
		// cout<<cnt;
		for (int i = 0; i < length; i++) {
			if (i == 0) printf("%d", res[i]);
			else printf("+%d", res[i]);
		}printf("\n");
	}
	else if (sum > n) return;
	else {
		// int myN=n-sum;
		//원래 n-1 
		for (int i = n - 1; i >= 0; i--) {
			res[length] = i;
			division(sum + i, length + 1);

		}
	}
}
int main() {
	cin >> n;
	division(0, 0);
	cout << cnt;
}