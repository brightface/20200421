#include <iostream>
#include <stdio.h>

using namespace std;

int arr[100];
int n, r;
void getRe(int x) {

	if (x >= r)
	{
		bool flag = false;

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < r; j++)
			{
				if (j != i && arr[i] == arr[j]) flag = true;
				// else cout<<char(arr[j]+97);
			}
		}

		if (flag == false)
		{
			for (int i = 0; i < r; i++)
			{
				printf("%c", arr[i] + 'a');
			}

			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			arr[x] = i;
			getRe(x + 1);
		}
	}
}

int main()
{
	cin >> n >> r;
	getRe(0);
}
