//complete

#include <iostream>

using namespace std;

int arr[] = { 3, 5, 4, 1, 2 };

int search(int ar[], int num)
{
	int i = sizeof(arr)/sizeof(arr[0]);

	for (int j = 0; j < i; j++)
	{
		if (ar[j] == num)
			return j;
	}
	return -1;
}

int main()
{
	int num;

	cout << "찾을 숫자를 입력하세요: ";
	cin >> num;

	int k = search(arr, num);
	if (k == -1)
		cout << "찾을 숫자가 없습니다" << endl;
	else
		cout << "찾는 숫자는 " << k + 1 << "번째에 있습니다." << endl;

	return 0;
}