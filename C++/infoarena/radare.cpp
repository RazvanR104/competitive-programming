#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3510, MOD = 31333;
typedef uint16_t u16;

int N, P;
int epos;
u16 pw2[NMAX], euler[NMAX], first[NMAX], last[NMAX], tsize[NMAX], cost[NMAX];
u16 DP[NMAX][NMAX];
vector<int> G[NMAX];

void DFS(int node, int from) {
    euler[++epos] = node;
    first[node] = epos;
    tsize[node] = 1;

    for (const int &it: G[node])
        if (it != from) {
            DFS(it, node);
            tsize[node] += tsize[it];
        }

    last[node] = epos + 1;
}

void Fix(u16 &value) {
    if (value >= MOD)
        value -= MOD;
}

int main() {
    assert(freopen("radare.in", "r", stdin));
    assert(freopen("radare.out", "w", stdout));

    int i, j;
    int x, y;

    cin >> N >> P;
    pw2[0] = 1;
    for (i = 1; i < N; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
        pw2[i] = pw2[i - 1] * 2 % MOD;
    }
    for (i = 1; i <= N; ++i)
        cin >> cost[i];

    DFS(1, -1);
    DP[1][0] = 1;
    for (i = 1; i <= N; ++i) {
        for (j = 0; j <= P; ++j) {
            if (DP[i][j] == 0)
                continue;
            if (j + cost[euler[i]] <= P)
                DP[i + 1][j + cost[euler[i]]] += DP[i][j];
            DP[last[euler[i]]][j] = DP[last[euler[i]]][j] + int(DP[i][j]) * pw2[tsize[euler[i]] - 1] % MOD;
            Fix(DP[i + 1][j + cost[euler[i]]]);
            Fix(DP[last[euler[i]]][j]);
        }
    }

    cout << DP[N + 1][P] << '\n';
    return 0;
}
