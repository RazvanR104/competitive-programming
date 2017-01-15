#include <bits/stdc++.h>

using namespace std;

const int NMAX = 20, inf = 0x3f3f3f3f;

int N, M;
int C[NMAX][NMAX], DP[1 << 18][NMAX];
vector<int> G[NMAX];

void Go(int mask, int last) {
    if (DP[mask][last] != -1)
        return;

    DP[mask][last] = inf;
    for (const int &it: G[last])
        if (mask & (1 << it)) {
            Go(mask ^ (1 << last), it);
            DP[mask][last] = min(DP[mask][last], DP[mask ^ (1 << last)][it] + C[it][last]);
        }
}

int main() {
    assert(freopen("hamilton.in", "r", stdin));
    assert(freopen("hamilton.out", "w", stdout));

    int x, y, c;

    cin >> N >> M;
    while (M--) {
        cin >> x >> y >> c;
        G[y].push_back(x);
        C[x][y] = c;
    }

    memset(DP, -1, sizeof DP);
    DP[1][0] = 0;

    int answer = inf;
    for (int i = 0; i < N; ++i)
        if (C[i][0]) {
            Go((1 << N) - 1, i);
            answer = min(answer, DP[(1 << N) - 1][i] + C[i][0]);
        }

    if (answer != inf)
        cout << answer << '\n';
    else
        cout << "Nu exista solutie\n";
    return 0;
}
