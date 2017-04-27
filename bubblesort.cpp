#include <iostream>

using namespace std;

int main()
{
	int arr[15] = { 12, 5, 9, 14, 1, 15, 2, 8, 11, 3, 7, 4, 13, 6, 10 };
	int last = 14;

	while (1)
	{
		int check = 0;

		for (int i = last - 1; i >= 0; i--)
		{
			if (arr[last] < arr[i])
			{
				swap(arr[last], arr[i]);
				check++;
			}
		}
		last--;
		if (check == 0)
			break;
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
//raj@thevirus.com
//TD2H9F - NRDGPW - JJUUN3 - 76DDQ1 - F6XA1C - FA5TBK - LXLDVA - 6MQWMA - FS69BX - JHV664 - XN7HFK - 2PZ2LA