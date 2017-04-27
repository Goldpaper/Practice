//예외 처리부분 처리불가 (ex: input값이 13이 들어올때) 무한루프에 빠짐

#include <iostream>

using namespace std;

int search(int arr[], int size, int num)
{
	int first = 0;
	int last = size - 1;
	int mid = (first + last)/2;

	while (first < last)
	{
		if (num < arr[mid])
		{
			last = mid;
			mid = (first + mid) / 2;
		}
		else if (num > arr[mid])
		{
			first = mid;
			mid = (last + mid +1) / 2;
		}
		else
			return mid+1;
	}
	return -1;
}

int main()
{
	int arr[] = {1, 10, 11, 100, 101, 110, 111, 1000, 1001, 1010 };
	int k;

	cout << "찾을 숫자를 입력하세요: ";
	cin >> k;

	int size = sizeof(arr) / sizeof(arr[0]);

	int location = search(arr, size, k);

	if (location == -1)
		cout << "찾는 숫자가 없습니다" << endl;
	else
		cout << "찾는 숫자는 " << location << "번째에 위치합니다" << endl;

	return 0;
}
