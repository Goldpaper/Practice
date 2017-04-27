#include<iostream>
#include<queue>
using namespace std;

int main() {
	int T, N, M;
	bool tr = 0;
		cin >> N >> M;
		queue<int> result;
		queue<int> que;
		int **PD = new int*[M];
		int *PDS = new int[M];
		int *degree = new int[N];
		int **right = new int*[N];
		int *rightcount = new int[N];
		int *rightccount = new int[N];
		for (int i = 0;i < N;i++) {
			degree[i] = 0;
			rightcount[i] = 0;
			rightccount[i] = 0;
		}
		for (int i = 0;i < M;i++) {
			cin >> PDS[i];
			PD[i] = new int[PDS[i]];
			for (int j = 0;j < PDS[i];j++) {
				cin >> PD[i][j];
			}
			for (int j = 0;j<PDS[i] - 1;j++) {
				rightcount[PD[i][j] - 1]++;
			}
		}

		for (int i = 0;i < N;i++) {
			right[i] = new int[rightcount[i]];
		}
		for (int i = 0;i < M;i++) {
			for (int j = 1;j < PDS[i];j++) {
				degree[PD[i][j] - 1]++;
				right[PD[i][j - 1] - 1][rightccount[PD[i][j - 1] - 1]] = PD[i][j];
				rightccount[PD[i][j - 1] - 1]++;
			}
		}
		int count = 0;
		for (int i = 0;i < N;i++) {
			if (degree[i] == 0) {
				que.push(i + 1);
				degree[i]--;
				for (int j = 0;j < rightcount[i];j++) {
					degree[right[i][j] - 1]--;

				}
				count++;
			}
		}
		while (!que.empty()) {
			int *front = new int[count];
			for (int i = 0;i < count;i++) {
				front[i] = que.front();
				que.pop();
			}
			for (int i = 0;i < count;i++) {
				for (int j = 0;j < count - 1;j++) {
					if (front[j] > front[j + 1]) {
						int temp = front[j];
						front[j] = front[j + 1];
						front[j + 1] = front[j];
					}
				}
			}
			for (int i = 0;i < count;i++) {
				result.push(front[i]);
			}
			count = 0;
			for (int i = 0;i < N;i++) {
				if (degree[i] == 0) {
					que.push(i + 1);
					degree[i]--;
					for (int j = 0;j < rightcount[i];j++) {
						degree[right[i][j] - 1]--;
					}
					count++;
				}
			}
		}
		if (result.size() == N)
		while (!result.empty()) {
			cout << result.front() << " ";
			result.pop();
		}
		else
			cout << 0 << endl;
}