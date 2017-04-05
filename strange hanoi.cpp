#include <iostream>
#include <stack>

using namespace std;

stack<int> st;
void hanoi(int n, int a, int b, int c, int l, int* disk, int &m, int n1)
{
	if (n == 1)
	{
		int k = disk[n1 - 1];
		while (k-- > 0)
		{
			m++;
			if ((c == 2) && (l >= m)) {
				st.push(n1);
			}
			if ((a == 2) && (l >= m))
			{
				st.pop();
			}
			if (l < m)
				break;
		}
	}
	else
	{
		hanoi(n - 1, a, c, b, l, disk, m, n - 1);
		hanoi(1, a, b, c, l, disk, m, n); 
		hanoi(n - 1, b, a, c, l, disk, m, n - 1);
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	int test_case;	//테스트케이스 받을 변수
	int N;		//원반의 종류(크기가 1번부터 N번까지 있음)
	int m;	//원반의 갯수
	int l;		//목표 이동수 l(L)

	cin >> test_case;	//테스트 케이스 수 입력받음
	while (test_case--)
	{
		cin >> N;
		int* disk = new int[N];
		int m = 0;
		for (int i = 0; i < N; i++)
			cin >> disk[i];

		cin >> l;

		hanoi(N, 1, 2, 3, l, disk, m, N);
		if (st.empty()==1)
			cout << 0;
		while (!st.empty())
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << endl;
	}
}
