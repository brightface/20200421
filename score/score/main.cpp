#include<iostream>
#include<fstream>
using namespace std;

int score[100][4];

int main() {
	//  학점 // 과목 // 평점
	int testCases = 1;
	ifstream in;
	in.open("input.txt");
	int cnt = 0;

	int cnt_score_sum = 0;
	int see_sum = 0;
	while (testCases--)
	{
		for (int j = 0; j < cnt; j++) {
			for (int i = 0; i < 3; i++) {
				in >> score[j][i];
			}
		}
		for (int j = 0; j < cnt; j++) {
			
			cnt_score_sum += score[j][1];
			
		}
	
	}

}