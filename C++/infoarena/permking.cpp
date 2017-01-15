#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;

int T, N, M;
int P[NMAX];

int main() {
	assert(freopen("permking.in", "r", stdin));
	assert(freopen("permking.out", "w", stdout));

	for (cin >> T; T; --T) {
		cin >> N >> M;
		for (int i = 1; i <= N; ++i)
			P[i] = N - i + 1;
		while (M--) {
			int x, y;
			cin >> x >> y;
			sort(P + x, P + y + 1);
		}
		int j;
		for (j = 1; j <= N && P[j] == j; ++j);
		if (j > N)
			cout << "1\n";
		else
			cout << "0\n";
	}

	return 0;
}
