#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25, BMAX = 1 << 18, inf = 0x3f3f3f3f;

int N, M;
int C[NMAX][NMAX];
vector<int> G[NMAX];
int DP[BMAX][NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("hamilton.in", "r", stdin) != NULL);
    assert(freopen("hamilton.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, k, x, y, c;

    cin >> N >> M;
    while (M--) {
        cin >> x >> y >> c;
        G[y].push_back(x);
        C[x][y] = c;
    }

    memset(DP, inf, sizeof(DP));
    DP[1][0] = 0;

    for (i = 2; i < (1 << N); ++i) {
        for (j = 0; j < N; ++j) {
            if (i & (1 << j)) {
                for (k = 0; k < G[j].size(); ++k) {
                    if (i & (1 << G[j][k])) {
                        DP[i][j] = min(DP[i][j], DP[i ^ (1 << j)][G[j][k]] + C[G[j][k]][j]);
                    }
                }
            }
        }
    }

    int answer = inf;
    for (i = 0; i < int(G[0].size()); ++i) {
        answer = min(answer, DP[(1 << N) - 1][G[0][i]] + C[G[0][i]][0]);
    }

    if (answer != inf)
        cout << answer << '\n';
    else
        cout << "Nu exista solutie\n";

	return 0;
}
