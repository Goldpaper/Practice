//너무 간단...

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
	cout << "7 팩토리얼의 값은 " << pibo(7)  << "입니다" << endl;
}