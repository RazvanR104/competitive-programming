#include <bits/stdc++.h>

using namespace std;

const int NMAX = 710;
const int inf = 0x3f3f3f3f;

int N, M;
char R[NMAX][NMAX];
uint16_t LMax[NMAX][NMAX], Next[NMAX][NMAX];

void generateTest() {
	ofstream out("rama.in");
	out << "700 700\n";
	srand(time(0));
	for (int i = 1; i <= 700; ++i) {
		for (int j = 1; j <= 700; ++j) {
			out << 1;
		}
		out << '\n';
	}
	out.close();
}

int main() {
	assert(freopen("rama.in", "r", stdin));
	assert(freopen("rama.out", "w", stdout));

	int i, j, k;
	int answer = 0;

	generateTest();

	cin >> N >> M;
	cin.ignore(1);
	for (i = 1; i <= N; ++i) {
		cin.getline(R[i] + 1, NMAX);
		for (j = 1; j <= M; ++j)
			R[i][j] -= '0';
	}

	for (j = 1; j <= M; ++j) {
		for (i = N; i >= 1; ) {
			if (R[i][j]) {
				int _i = i;
				while (i > 0 && R[i][j])
					LMax[i--][j] = _i;
			} else
				--i;
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = M; j >= 1; ) {
			if (R[i][j]) {
				int _j = j;
				do {
					Next[i][--j] = _j;
				} while (j > 0 && !R[i][j]);
			} else
				--j;
		}
	}

	for (i = 1; i <= N; ++i) {
		for (j = i; j <= N; ++j) {
			k = 1;
			if (R[i][1] == 0) {
				if (Next[i][k] == 0 || Next[j][k] == 0)
					break;
				k = max(Next[i][1], Next[j][1]);
			}
			int curr = LMax[i][k] >= j;
			while (k > 0) {
				if (LMax[i][k] >= j) {
					if (curr == 0)
						++curr;
					answer = max(answer, curr * (j - i + 1));
				}
				if (Next[i][k] == 0 || Next[j][k] == 0)
					break;
				int next = max(Next[i][k], Next[j][k]);
				if (next != k + 1) {
					curr = LMax[i][next] >= j;
				} else if (curr)
					++curr;
				k = next;
			}
		}
	}

	cout << answer << '\n';
	return 0;
}
