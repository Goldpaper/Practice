//2번 배열
#include <iostream>
#include <queue>
//#include <fstream>
#define Max 250

using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	int T, M, N, K, L, num;
	int hp, col, row;
	int a_hp, a_col, a_row;
	int b_hp, b_col, b_row;
	int n1, n2, n3, n4, mul1, mul2, sub1, sub2, sub3, sub4, subA, subB;
	bool brk1, brk2;
	int ai, bi;
	cin >> T;
	
	while (T--) {
		int board[Max][Max];
		int A[2500];
		int B[2500];
		ai = 0; bi = 0;
		//queue<int> A;
		//queue<int> B;
		cin >> M >> N;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> num;
				board[i][j] = num;
			}
		}
		cin >> K;
		while (K--) {
			ai = 0; bi = 0;
			cin >> L;
			for (int i = 0; i < L; i++) {
				cin >> num;
				A[ai] = num;
				ai++;
				//A.push(num);
			}
			for (int i = 0; i < L; i++) {
				cin >> num;
				B[bi] = num;
				bi++;
				//B.push(num);
			}
			cin >> hp >> col >> row;
			a_hp = hp;
			a_col = col;
			a_row = row;
			b_hp = hp;
			b_col = col;
			b_row = row;

			ai = 0; bi = 0;
			while (true) {
				//A차례
				/*
				n1 = A.front();
				A.pop();
				A.push(n1);
				n2 = A.front();
				A.pop();
				A.push(n2);
				*/
				n1 = A[ai];
				A[ai + L] = n1;
				ai++;
				n2 = A[ai];
				A[ai + L] = n2;
				ai++;
				mul1 = n1*n2;

				n3 = B[bi];
				B[bi + L] = n3;
				bi++;
				n4 = B[bi];
				B[bi + L] = n4;
				bi++;
				mul2 = n3*n4;
				
				/*brk1 = false; brk2 = false;
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						if (board[i][j] == mul1) {
							sub1 = i - b_col;
							sub2 = j - b_row;
							b_col = i;
							b_row = j;
							brk1 = true;
						}
						else if (board[i][j] == mul2) {
							sub3 = i - a_col;
							sub4 = j - a_row;
							a_col = i;
							a_row = j;
							brk1 = true;
						}
						if ((brk1 + brk2) == 2) break;
					}					
				}*/
				brk1 = false;
				/*if (board[b_col][b_row] == mul1) {
					sub1 = 0;
					sub2 = 0;
					brk1 = true;
					break;
				}*/
				int temp = 0;
				while (!brk1) {
					for (int i = b_col - temp; i <= b_col + temp; i++) {
						for (int j = b_row - temp; j <= b_row + temp; j++) {
							if (i > M || j > N || i < 0 || j < 0)
								continue;
							if (board[i][j] == mul1) {
								sub1 = i - b_col;
								sub2 = j - b_row;
								b_col = i;
								b_row = j;
								brk1 = true;
								break;
							}
						if (brk1) break;
						}
					}
					if (brk1 == false)
						temp++;
				}

				if (sub1 < 0)
					sub1 *= -1;
				if (sub2 < 0)
					sub2 *= -1;
				subB = sub1 + sub2;
				b_hp -= subB;
				if (b_hp <= 0) {
					cout << "A" << endl;
					break;
				}
				
				
				brk1 = false;
				temp = 0;
				while (true) {
					for (int i = a_col - temp; i <= a_col + temp; i++) {
						for (int j = a_row - temp; j <= a_row + temp; j++) {
							if (i > M || j > N || i < 0 || j < 0)
								continue;
							if (board[i][j] == mul1) {
								sub3 = i - a_col;
								sub4 = j - a_row;
								a_col = i;
								a_row = j;
								brk1 = true;
								break;
							}
							if (brk1) break;
						}
					}
					if (brk1 == false)
						temp++;
					else break;
				}

				if (sub3 < 0)
					sub3 *= -1;
				if (sub4 < 0)
					sub4 *= -1;
				subA = sub3 + sub4;
				a_hp -= subA;
				if (a_hp <= 0) {
					cout << "B" << endl;
					break;
				}
			}
		}
	}
}