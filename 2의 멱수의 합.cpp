#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>

const int MOD = 1000000000;

int N, p[25], dp[1000005][25];

int D(int i, int j) {
//	printf("%d %d\n", i, j);

	if (i < 0) return 0;
	if (i == 0 || (i > 0 && j == 1)) return 1;
	
	int &ret = dp[i][j];
	if (ret != -1) return ret;

	return ret = (D(i, j - 1) % MOD + D(i - p[j], j) % MOD) % MOD;
}

int main() {
	p[1] = 1;
	for (int i = 2; i <= 20; ++i) {
		p[i] = 1;
		p[i] *= p[i - 1] * 2;
	}

	scanf("%d", &N);

	memset(dp, -1, sizeof(dp));
	printf("%d", D(N, 20));
}