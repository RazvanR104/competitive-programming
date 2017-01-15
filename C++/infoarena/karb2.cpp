#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, MOD = 666013;

int N, K;
int cartel[NMAX], DP[2][NMAX];
int lt[NMAX], rt[NMAX];
vector<int> G[NMAX];

void DFS(int node, int from) {
    int sons = 0;
    for (int i = 0; i < int(G[node].size()); ++i) {
        int it = G[node][i];
        if (it == from)
            continue;
        DFS(it, node);
        ++sons;
    }

    if (sons == 0) {
        if (cartel[node]) {
            DP[0][node] = 1;
            DP[1][node] = 0;
        } else {
            DP[0][node] = 0;
            DP[1][node] = 1;
        }
        return;
    }

    lt[0] = 1;
    int product = 1;
    for (int i = 0; i < int(G[node].size()); ++i) {
        int it = G[node][i];
        if (it == from) {
            lt[i + 1] = lt[i];
            continue;
        }
        product = 1ll * product * (DP[0][it] + DP[1][it]) % MOD;
        lt[i + 1] = product;
    }

    product = 1;
    rt[G[node].size() + 1] = 1;
    for (int i = int(G[node].size()) - 1; i >= 0; --i) {
        int it = G[node][i];
        if (it == from) {
            rt[i + 1] = rt[i + 2];
            continue;
        }
        product = 1ll * product * (DP[0][it] + DP[1][it]) % MOD;
        rt[i + 1] = product;
    }

    DP[1][node] = product;

    int sum = 0;
    for (int i = 0; i < int(G[node].size()); ++i) {
        int it = G[node][i];
        if (it == from)
            continue;
        sum = (sum + (1ll * lt[i] * rt[i + 2] * DP[0][it] % MOD)) % MOD;
    }
    DP[0][node] = sum;

    if (cartel[node]) {
        DP[0][node] = DP[1][node];
        DP[1][node] = 0;
    }
}

int main() {
    assert(freopen("karb2.in", "r", stdin));
    assert(freopen("karb2.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &K);
    for (i = 1; i <= K; ++i) {
        scanf("%d", &j);
        cartel[j] = 1;
    }

    for (i = 1; i < N; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, -1);
    cout << DP[0][1] << '\n';

    return 0;
}
