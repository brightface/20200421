#include <iostream>
using namespace std;
int arr[5][5];
int check[5][5];
// int (*numPtr)[5];
int ans[5][5] = { 1, };

int bingo(int pan[][5],int size	) {
	int a_cnt = 0;
	int bingo_cnt = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			
			if (pan[i][j] == 99) {
				a_cnt++;
				if (j == 4) {
					if (a_cnt == 5) {
						bingo_cnt++;
						a_cnt = 0;
					}
					else a_cnt = 0;
				}

				
			}
			

		}
	}
	a_cnt = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (a_cnt == 5) {
				bingo_cnt++;
				a_cnt = 0;
			}
			if (pan[j][i] == 99) {
				a_cnt++;
				if (j == 4) {
					if (a_cnt == 5) {
						bingo_cnt++;
						a_cnt = 0;
					}
					else a_cnt = 0;
				}
			}
			
		}
	}
	a_cnt = 0;
	for (int i = 0; i < 5; i++) {
		if (a_cnt == 5) {
			bingo_cnt++;
			a_cnt = 0;
		}
		if (pan[i][i] == 99) {
			a_cnt++;
			if (i == 4) {
				if (a_cnt == 5) {
					bingo_cnt++;
					a_cnt = 0;
				}
				else a_cnt = 0;
			}
		}
		
	}
	a_cnt = 0;

	for (int i = 0; i < 5; i++) {
		if (a_cnt == 5) {
			bingo_cnt++;
			a_cnt = 0;
		}
		if (pan[4 - i][4 - i] == 99) {
			a_cnt++;
			if (i == 4) {
				if (a_cnt == 5) {
					bingo_cnt++;
					a_cnt = 0;
				}
				else a_cnt = 0;
			}
		}
	}
	a_cnt = 0;

	if (bingo_cnt >= 3) {
		return 1;

	}return 0;
	

}

int main() {
	for (int k = 0; k < 5; k++) {
		for (int w = 0; w < 5; w++) {
			cin >> arr[k][w];
			check[k][w] = arr[k][w];
		}
	}
	//by input
	int finish = 0;
	int tmp;
	int print;
	int flag = 0;
	for (int m = 0; m < 25; m++) {
		cin >> tmp;
		

		//search
		for (int k = 0; k < 5; k++) {
			for (int w = 0; w < 5; w++) {
				
				if (tmp == arr[k][w]) {
					arr[k][w] = 99;
					finish++;
					if ((bingo(arr, 25) == 1) && (flag == 0)) {
						flag = 1;
						print = finish;
					}
					//check
					else if (bingo(arr, 25) == 0) {
						  check[k][w] = 99;
						  
					}
					
				}
			}
		}
		
	}
	cout << print << endl;;
	 

	 for(int k=0;k<5;k++){
		 for (int w = 0; w < 5; w++) {
			 cout<<check[k][w] << " ";
		 }cout << endl;
	
	 }

	//cout << finish;

	return 0;
}