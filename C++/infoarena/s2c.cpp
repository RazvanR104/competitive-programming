#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010;

int N, V[NMAX];
int DP[NMAX][NMAX], pos[NMAX];

struct Compare {
    bool operator()(const int &lhs, const int &rhs) const {
        return V[lhs] < V[rhs];
    }
};

int Solve() {
    int i, j, k, answer = min(2, N);

    memset(DP, 0, sizeof(DP));

    for (i = 1; i <= N; ++i)
        pos[i] = i;
    sort(pos + 1, pos + N + 1, Compare());
    V[0] = 1e9;

    for (i = 1; i <= N; ++i) {
        for (j = N - 1; j >= 1; --j)
            if (DP[i][j + 1] && (DP[i][j] == 0 || V[DP[i][j + 1]] < V[DP[i][j]]))
                DP[i][j] = DP[i][j + 1];

        int longest = 1;
        for (k = 1; k <= N; ++k) {
            j = pos[k];
            if (j <= i)
                continue;

            while (V[DP[i][longest + 1]] < V[j])
                ++longest;

            if (DP[j][longest + 1] == 0 || V[i] < V[DP[j][longest + 1]])
                DP[j][longest + 1] = i;

            answer = max(answer, longest + 1);
        }
    }

    return answer;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("s2c.in", "r", stdin) != NULL);
    assert(freopen("s2c.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, T;

    for (cin >> T; T; --T) {
        cin >> N;
        for (i = 1; i <= N; ++i)
            cin >> V[i];
        cout << Solve() << '\n';
    }

	return 0;
}
