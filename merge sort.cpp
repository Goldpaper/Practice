#include <iostream>

using namespace std;

int arr[15] = { 12, 5, 9, 14, 1, 15, 2, 8, 11, 3, 7, 4, 13, 6, 10 };
int arrtemp[15] = { 0 };

void devide(int, int);
void merge(int, int);
void print();

int main()
{
	devide(0, 14); print();
}

void devide(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		devide(left, mid);
		devide(mid + 1, right);
		merge(left, right);
	}
}

void merge(int left,int right)
{
	int mid = (left + right) / 2;
	int leftp = left;				//left pivot
	int rightp = mid + 1;			//right pivot
	int count = 0;

	while ((leftp <= mid) && (rightp <= right))
	{
		if (arr[leftp] > arr[rightp])
		{
			arrtemp[count] = arr[rightp];
			rightp++;
			count++;
		}
		else
		{
			arrtemp[count] = arr[leftp];
			leftp++;
			count++;
		}
	}

	while (leftp <= mid)
	{
		arrtemp[count] = arr[leftp];
		leftp++;
		count++;
	}

	while (rightp <= right)
	{
		arrtemp[count] = arr[rightp];
		rightp++;
		count++;
	}

	for (int i = 0; i < count; ++i)
	{
		arr[left] = arrtemp[i];
		left++;
	}
}

void print()
{
	for (int i = 0; i < 15; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}