#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

int result[100];
char inp[15];
int arr[15];
bool check[10];
bool printmin;
bool printmax;
int n;
void getMax(int x) {
	if (printmax) return;
	if (x > n) {
		for (int i = 0; i < n + 1; i++)
			printf("%d", arr[i]);
		printf("\n");
		printmax = true;
	}

	else
	{
		for (int i = 9; i >= 0; i--)
		{
			bool flag = false;
			arr[x] = i;

			if (check[i] == false)
			{
				if (x == 0) flag = true;
				if (inp[x - 1] == '>')
				{
					if (arr[x - 1] > arr[x])
					{
						// cout<<arr[x-1]<<":check"<<x-1<<endl;
						flag = true;
					}
				}
				else
				{ // <
					if (arr[x - 1] < arr[x])
					{
						flag = true;
					}
				}

				if (flag)
				{
					check[i] = true;
					getMax(x + 1);
					check[i] = false;
				}
			}
		}
	}
}
void getMin(int x)
{ //x번째 수를 정하는 함수
	if (printmin) return;
	if (x > n)
	{
		for (int i = 0; i < n + 1; i++) {
			printf("%d", arr[i]);
		}printf("\n");
		printmin = true;
	}
	else
	{
		for (int i = 0; i <= 9; i++)
		{
			arr[x] = i; //

			if (check[i] == false)
			{

				bool flag = false;

				if (x == 0) flag = true; //앞에 숫자가 없어
				else if (inp[x - 1] == '<') //여기 x-1 이어야해 
				{
					if (arr[x - 1] < arr[x]) {
						flag = true;
					}
				}
				else // ">"
				{
					if (arr[x - 1] > arr[x]) {
						flag = true;
					}
				}
				if (flag == true)
				{
					check[i] = true;
					getMin(x + 1);
					check[i] = false;
				}
			}
		}
	}
}



int main()
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		cin >> inp[i];
	}


	getMax(0);
	getMin(0);
	memset(check, 0, sizeof(check));
	cout << endl;
}