#include <iostream>

using namespace std;

void swap(int&, int&);

int main()
{
	int arr[15] = { 12, 5, 9, 14, 1, 15, 2, 8, 11, 3, 7, 4, 13, 6, 10 };
	int last = 14;

	for (int i = 0; i < 15; i++)
	{
		int large = 0;
		for (int index = 0; index <= last; index++)
		{
			if (arr[index]>arr[large])
				large = index;
		}
		swap(arr[large], arr[last]);
		last--;
	}

	for (int i = 0; i < 15; i++)
		cout << arr[i] << " ";
	cout << endl;
}


void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}