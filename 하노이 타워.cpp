//프로그램은 간단하지만 생각할 게 많다.

#include <iostream>

using namespace std;

void hanoi(int num, char from, char temp, char to)
{
	if (num == 1)
		cout << from << " -> " << to << endl;
	else
	{
		hanoi(num - 1, from, to, temp);
		hanoi(1, from, temp, to);
		hanoi(num - 1, temp, from, to);
	}
}

int main()
{
	int num;
	cout << "하노이 타워 문제를 해결해보자" << endl;
	cout << "원반이 몇개 쌓여있는가? ";
	cin >> num;
	hanoi(num, 'A', 'B', 'C');
	return 0;
}