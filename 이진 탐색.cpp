//���� ó���κ� ó���Ұ� (ex: input���� 13�� ���ö�) ���ѷ����� ����

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

	cout << "ã�� ���ڸ� �Է��ϼ���: ";
	cin >> k;

	int size = sizeof(arr) / sizeof(arr[0]);

	int location = search(arr, size, k);

	if (location == -1)
		cout << "ã�� ���ڰ� �����ϴ�" << endl;
	else
		cout << "ã�� ���ڴ� " << location << "��°�� ��ġ�մϴ�" << endl;

	return 0;
}
