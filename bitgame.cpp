#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);
	int test_case;	// 테스트 케이스 갯수
	int N;			// 차례
	

	cin >> test_case;
	for (test_case; test_case > 0; test_case--)
	{
		cin >> N;

		int count = 1;	// 자리수
		int co_ex = 2;	// 자리수 * 지수
		int *arr = new int[10000];

		if (N == 1)
		{
			cout << "0" << endl;
			continue;
		}

		while(N > co_ex)
		{
			count++;
			co_ex += count*(int)pow(2,(count-1));
		}
		
		N -= co_ex-(count*(int)pow(2, (count - 1)))+1;

		for (int i = 1; i <= count; i++)
			arr[i] = 0;
		arr[1] = 1;

		int q = (int)(N / count);		//몫
		int r = N % count;				//나머지
		
		for(int i = count; i >= 2; i--)
		{
			if (q % 2 == 0)
				arr[i] = 0;
			else
				arr[i] = 1;
			q /= 2;
		}
		cout << arr[r + 1] << endl;

		delete arr;
	}
	return 0;
}