#include <iostream>

#define Max 501
using namespace std;

int people[Max][Max]; //�� ������ �������踦 ��Ÿ��
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
    std::ios::sync_with_stdio(false);
    int test_case;    //�׽�Ʈ���̽� ���� ����
    int N, M;	 //���� ������ ��, ������ ��
    int s, e;	 //������ ����(start)�� ��(end)�� ��Ÿ��
    cin >> test_case; //�׽�Ʈ ���̽� �� �Է¹���
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
	cin >> N >> M;		     //������ ��, ������ �� �Է¹���
	for (int i = 1; i <= N; i++) //�α����� �Է¹���
	    cin >> people[i][0];     //������ �������迡�� �������� �ʴ� 0���� Ȱ���Ͽ� �α��� ����

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
	    int len = 0;     //�Ÿ��ݰ�
	    int len_sum = 0; //�Ÿ���
	    for (int j = 1; j <= N; j++)
	    {
		if (i == j)
		    continue;
		if (len < temp[i][j])
		    len = temp[i][j];
		len_sum += temp[i][j];
	    }

	    xi[i] = (N - 1) * len + len_sum;
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
