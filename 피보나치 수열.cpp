//�ʹ� ����...

#include <iostream>

using namespace std;

int pibo(int num)
{
	int count = num-1;
	
	while (count != 1)
	{
		num *= count;
		count--;
	}
	return num;
}

int main()
{
	cout << "7 ���丮���� ���� " << pibo(7)  << "�Դϴ�" << endl;
}