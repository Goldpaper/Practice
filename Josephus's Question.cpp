#include <iostream>

using namespace std;

int main()
{
	int arr[41] = { 0 };
	int count=2;
	int deadcount=0;
	while (1)
	{
		if (arr[count] == 0)
		{
			arr[count] = 1;
			deadcount++;

			if (deadcount == 39)
				break;
		}
		
		while (arr[count] == 1)
			count++;
		count++;
		while (arr[count] == 1)
			count++;
		count++;
		while (arr[count] == 1)
			count++;

		if (count >= 41)
			count -= 41;
	}

	cout << "살아있는 사람은? ";
	for (int i = 0; i < 41; i++)
	{
		if (arr[i] == 0)
			cout << i+1 << " ";
	}
	cout << " 입니다." << endl;

	return 0;
}