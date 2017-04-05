#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

#define max_singer 1003

using namespace std;

int main()
{
	std::ios::sync_with_stdio(false);	int test_case;
	int N, M;
	int singer_num;
	int sorted_list[max_singer];
	int singer_list[max_singer];
	vector<int> singer_vector[max_singer];
	priority_queue<int, vector<int>, greater<int>> linked_queue;
	priority_queue<int, vector<int>, greater<int>> empty;

	cin >> test_case;
	while (test_case--)
	{
		swap(linked_queue, empty);
		int temp[max_singer] = { 0 };
		for (int i = 1; i <= max_singer; i++)
			singer_vector[i].clear();

		cin >> N >> M;
		while (M--)
		{
			cin >> singer_num;
			for (int i = 1; i <= singer_num; i++)
				cin >> singer_list[i];

			for (int i = 1; i < singer_num; i++)
			{
				temp[singer_list[i + 1]]++;
				singer_vector[singer_list[i]].push_back(singer_list[i + 1]);
				singer_list[i] = 0;
			}
			singer_list[singer_num] = 0;
		}

		for (int i = 1; i <= N; i++)
			if (temp[i] == 0)
				linked_queue.push(i);

		bool check = true;

		for (int i = 1; i <= N; i++)
		{
			if (linked_queue.empty())
			{
				cout << 0 << endl;
				check = false;
				break;
			}
			int front = linked_queue.top();
			sorted_list[i] = front;
			linked_queue.pop();

			for (int next : singer_vector[front])
				if (!(--temp[next]))
					linked_queue.push(next);
		}

		if (!check)
			continue;

		for (int i = 1; i <= N; i++)
			cout << sorted_list[i] << " ";
		cout << endl;
	}
}

