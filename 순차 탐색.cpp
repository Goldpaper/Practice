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

	cout << "ã�� ���ڸ� �Է��ϼ���: ";
	cin >> num;

	int k = search(arr, num);
	if (k == -1)
		cout << "ã�� ���ڰ� �����ϴ�" << endl;
	else
		cout << "ã�� ���ڴ� " << k + 1 << "��°�� �ֽ��ϴ�." << endl;

	return 0;
}