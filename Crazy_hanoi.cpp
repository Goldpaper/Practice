#include <iostream>
#include <stack>

#define Max 101

using namespace std;

int disc[Max];
int l;
stack<int> hanoi_2;

void hanoi(int, int, int, int, int);

int main()
{
	std::ios::sync_with_stdio(false);	int test_case;	
	int N;		
	
	cin >> test_case;	
	while (test_case--)
	{
		disc[0] = 0;
		
		cin >> N;
		for (int i = 1; i <= N; i++)
			cin >> disc[i];
		cin >> l;

		hanoi(N, N, 1, 2, 3);
		if (!(hanoi_2.empty()-1))
		{
			cout << 0 << endl;
			continue;
		}
		while (!hanoi_2.empty())
		{
			cout << hanoi_2.top() << " ";
			hanoi_2.pop();
		} cout << endl;
	}
}

void hanoi(int N, int arr_num, int one, int two, int three)
{
	if (!(N-1))
	{
		int disc_num = disc[arr_num];
		while (disc_num--)
		{
			disc[0]++;
			if (l >= disc[0])
			{
				if (!(three-2)) hanoi_2.push(arr_num);
				if (!(one-2)) hanoi_2.pop();
			}
			else break;	
		}
	}
	else
	{
		hanoi(N - 1, N - 1, one, three, two);
		hanoi(1, N, one, two, three);
		hanoi(N - 1, N - 1, two, one, three);
	}
}