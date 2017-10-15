#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5 + 10;

int T, N, Q;
int V[NMAX];

int main() {
	assert(freopen("debug.in", "r", stdin));
	assert(freopen("debug.out", "w", stdout));

	int i, j;

	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> N >> Q;
		for (i = 1; i <= N; ++i)
			cin >> V[i];
		cout << "Case #" << t << ":\n";
		for (i = 1; i <= Q; ++i) {
			int l, r, k;
			cin >> l >> r >> k;
			int answer = numeric_limits<int>::max();
			for (j = l; j <= r; ++j)
				answer = min(answer, abs(V[j] - k));
			cout << answer << '\n';
		}
	}

	return 0;
}
