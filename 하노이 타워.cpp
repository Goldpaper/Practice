//���α׷��� ���������� ������ �� ����.

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
	cout << "�ϳ��� Ÿ�� ������ �ذ��غ���" << endl;
	cout << "������ � �׿��ִ°�? ";
	cin >> num;
	hanoi(num, 'A', 'B', 'C');
	return 0;
}