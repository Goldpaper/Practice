#include <iostream>

using namespace std;

void comeback(int[], int, int);

int main()
{
	int arr[15] = { 12, 5, 9, 14, 1, 15, 2, 8, 11, 3, 7, 4, 13, 6, 10 };
	int pivot = arr[14];	// ÇÇ¹şÀº ¾Ï²¨³ª Àâ¾Æµµ µÊ, ÇöÀç´Â 10
	int first = 0;
	int last = 14;

	comeback(arr, first, last);

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

int quicksort(int arr[], int first, int last)
{
	int pivot = arr[last];
	int temp = last;
	last -= 1;

	while (first <= last)
	{
		while (pivot > arr[first]) first++;
		while (pivot < arr[last]) last--;
		if (first <= last)
			swap(arr[first], arr[last]);
	}
	swap(arr[first], arr[temp]);
	return (first);
	
}
 
void comeback(int arr[], int bigin, int end)
{
	if (bigin < end)
	{
		int tempnum = quicksort(arr, bigin, end);
		comeback(arr, bigin, tempnum-1);
		comeback(arr, tempnum+1, end);
	}
}