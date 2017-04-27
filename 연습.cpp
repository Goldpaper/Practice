#include <iostream>

using namespace std;

int main()
{
	int num;
	int sum = 1;

	cin >> num;
	
	for (int i = num; i > 1; i--)
	{
		sum = sum*i;
	}

	cout << sum << endl;
}