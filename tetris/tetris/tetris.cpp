﻿#include <iostream>
using namespace std;

// int arr[22][22] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
int arr[22][22];
int max_cnt0[22];
int min_cnt1[22];
int max0 = 0;

int main() {
	int row, col;
	cin >> col >> row;

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			arr[i][j] = 1;
		}
	}

	for (int i = 1; i < row + 1; i++) {
		for (int j = 1; j < col + 1; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i < col + 1; i++) {
		for (int j = 1; j < row + 1; j++) {
			if (arr[j][i] == 0) {
				max_cnt0[i]++;
			}
			else if (arr[j][i] == 1) {
				break;//min_cnt1++ 가 아니다.
			}
		}
	}

	int k = 1;
	max0 = max_cnt0[1];//y
	//1부터 양옆 줄 비교해서 최소값의 1개수가 y이다
	//일단 x부터찾기
	for (int i = 1; i < row + 1; i++) {
		if (max_cnt0[i] > max0)
		{
			max0 = max_cnt0[i]; //y
			k = i; //x
		}
	} //result x; 
	//예외를 먼저 처리// 논리로 
	//논리를 파고들어서 확장시킨다.


	int y = max0;

	int tmp = 0;
	if (y <= 3) {
		// cout<<0;
		// return 0;
		for (int i = y; i >= 1; i--) {
			arr[k][i] = 1;
		}
	}
	else {
		for (int i = y; i >= y - 4; i--) {
			arr[i][k] = 1;
		}
	}

	for (int i = y; i >= 1; i--) {
		for (int j = 1; j < col + 1; j++) {
			if (arr[i][j] == 0) break;
			else {
				if (j == col) tmp++;
			}
		}
	}

	// int y=row - min_cnt1[k];//y 좌표 no!
	// for (int i=1; i<row+1; i++){
	//   if(arr[i][k]==1){
	//     y=i;
	//   }
	//   else y = row - min_cnt1[k];
	// }
  //   for (int i = 1; i < row + 1; i++) {
  // 		for (int j = 1; j < col + 1; j++) {
  // 			if (arr[j][i] == 1) {
  // 				min_cnt1[j]++; 
  // 			}
  // 			else if (arr[j][i] == 1) {
  // 				break;//min_cnt1++ 가 아니다.
  // 			}
  // 		}
  // 	}


	cout << k << " " << tmp;
	return 0;

}