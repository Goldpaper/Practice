#include <iostream>

#define Max 501
using namespace std;

int people[Max][Max];	//각 도시의 연결관계를 나타냄
int temp[Max][Max];
int result[Max][Max];

int Matrix(int arr[Max][Max], int p, int q, int m)
{
	int temp = 0;
	for (int i = 1; i <= m; i++)
		temp += arr[p][i] * people[i][q];
	return temp;
}

int main()
{
	std::ios::sync_with_stdio(false);	int test_case;	//테스트케이스 받을 변수
	int N, M;		//각각 도시의 수, 도로의 수
	int s, e;		//도로의 시작(start)과 끝(end)을 나타냄
	cin >> test_case;	//테스트 케이스 수 입력받음
	while (test_case--)
	{
		for (int i = 0; i < Max; i++)
		{
			for (int j = 0; j < Max; j++)
			{
				people[i][j] = 0;
				temp[i][j] = 0;
				result[i][j] = 0;
			}
		}
		cin >> N >> M;	//도시의 수, 도로의 수 입력받음
		for (int i = 1; i <= N; i++)	//인구수를 입력받음
			cin >> people[i][0];		//도시의 연결관계에서 사용하지 않는 0열을 활용하여 인구수 저장

		for (int i = 1; i <= M; i++)
		{
			cin >> s >> e;
			people[s][e] = 1;
			people[e][s] = 1;
			temp[s][e] = 1;
			temp[e][s] = 1;
			result[s][e] = 1;
			result[e][s] = 1;
		}

		int count = 2;
		int N_temp = N;
		while (N_temp--)
		{
			for (int i = 1; i <= N; i++)
			{
				for (int j = 1; j <= N; j++)
				{
					if (i == j)
						continue;
					if (!temp[i][j])
					{
						result[i][j] = Matrix(temp, i, j, N);
						if (!result[i][j])
							result[i][j] = count;
					}
				}
			}
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					temp[i][j] = result[i][j];
			count++;
		}
	

		int xi[Max];
		for (int i = 1; i <= N; i++)
		{
			int len = 0;	//거리반경
			int len_sum = 0;	//거리합
			for (int j = 1; j <= N; j++)
			{
				if (i == j)
					continue;
				if (len < temp[i][j])
					len = temp[i][j];
				len_sum += temp[i][j];
			}

			xi[i] = (N - 1)*len + len_sum;
		}

		int min = xi[1];
		int sudo = 1;
		for (int i = 2; i <= N; i++)
		{
			if (min > xi[i])
			{
				min = xi[i];
				sudo = i;
			}
			else if (min == xi[i])
				people[sudo][0] > people[i][0] ? sudo = sudo : sudo = i;
		}
		cout << sudo << endl;
	}
	return 0;
}
