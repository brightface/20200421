#include <iostream>
using namespace std;
int testCases, n;

int main() {
	cin >> testCases;
	while (testCases--) {
		cin >> n;
		for (int i = 0; i <= n / 2; i++) {
			if (i <= (n / 2))
			{
				int cnt = 1;
				int k = n - (i * 2); // - //
				for (int j = 0; j < i; j++) { cout << "-"; }
				if (k >= 1)
				{
					while (1) {
						//cnt 1 , k 3
						cnt++;
						cout << "*" ;
						if (cnt > k) break;
						//cnt 2 k 3
						cnt++;
						cout << "+" ;

						if (cnt > k) break;
					}
				}

				for (int j = 0; j < i; j++) { cout << "-" ; }
				cout << endl;
			}
		}
		int tmpK = (n / 2) - 1;
		for (int i = n; i > (n + 1) / 2; i--)
		{	//5 4
			int cnt = 0;
			int ansK = n-(tmpK*2);
			
			for (int j = 0; j < tmpK; j++) {
				cout << "-";
			}
			if (ansK >= 1)
			{
				while (1) {
					//cnt 0 , k 3
					cout << "*" ;
					cnt++; //1
					if (cnt >= ansK) break;
					//cnt  k 3
					cout << "+" ;
					cnt++;//2

					if (cnt >= ansK) break;
				}
			}
			for (int j = 0; j < tmpK; j++) {
				cout << "-" ;
			}
			tmpK--;
			cout << endl;
		}
	}
}