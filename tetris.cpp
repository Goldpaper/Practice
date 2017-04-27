#include <iostream>
#include <string>
using namespace std;


/*
int main()
{
	while (1)
	{
		string a;
		getline(cin,a);
		if (a == "#")
			break;
	}
	
}
*/


int main()
{
	while (1)
	{
		char a[100];
		gets(a);
		for (int i = 0; i < 100; i++)
		{
			if (a[i] == ' ')
				a[i] == '%20';
		}

		for (int i = 0; i < 100; i++)
		{
			cout << a[i];
		}
		
		if (a[0] == '#')
			break;
	}
}