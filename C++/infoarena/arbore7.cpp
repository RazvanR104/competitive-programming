#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, MOD = 1e9 + 7;

int N;
int DP[2][2][NMAX];
vector<int> T[NMAX];

void DFS(int node, int from) {
    bool leaf = 1;
    for (const int &it: T[node]) {
        if (it == from)
            continue;
        leaf = 0;
        DFS(it, node);
    }

    if (leaf) {
        DP[0][0][node] = 1;
        DP[0][1][node] = 0;
        DP[1][0][node] = 1;
        DP[1][1][node] = 1;
    } else {
        DP[0][0][node] = 1;
        DP[1][0][node] = 1;
        DP[1][1][node] = 1;
        for (const int &it: T[node]) {
            if (it == from)
                continue;
            if (DP[0][0][it] - 1 > DP[0][1][it]) {
                DP[0][0][node] += DP[0][0][it] - 1;
                DP[1][0][node] = 1ll * DP[1][0][node] * DP[1][0][it] % MOD;
            } else if (DP[0][0][it] - 1 < DP[0][1][it]) {
                DP[0][0][node] += DP[0][1][it];
                DP[1][0][node] = 1ll * DP[1][0][node] * DP[1][1][it] % MOD;
            } else {
                DP[0][0][node] += DP[0][1][it];
                DP[1][0][node] = 1ll * DP[1][0][node] * (DP[1][1][it] + DP[1][0][it]) % MOD;
            }

            if (DP[0][0][it] > DP[0][1][it]) {
                DP[0][1][node] += DP[0][0][it];
                DP[1][1][node] = 1ll * DP[1][1][node] * DP[1][0][it] % MOD;
            } else if (DP[0][0][it] < DP[0][1][it]) {
                DP[0][1][node] += DP[0][1][it];
                DP[1][1][node] = 1ll * DP[1][1][node] * DP[1][1][it] % MOD;
            } else {
                DP[0][1][node] += DP[0][0][it];
                DP[1][1][node] = 1ll * DP[1][1][node] * (DP[1][0][it] + DP[1][1][it]) % MOD;
            }
        }
    }
}

int main() {
    assert(freopen("arbore7.in", "r", stdin));
    assert(freopen("arbore7.out", "w", stdout));

    int i, j, x, y;

    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        T[x].push_back(y);
        T[y].push_back(x);
    }

    DFS(1, -1);

    if (DP[0][0][1] > DP[0][1][1])
        cout << DP[0][0][1] << ' ' << DP[1][0][1] << '\n';
    else if (DP[0][0][1] < DP[0][1][1])
        cout << DP[0][1][1] << ' ' << DP[1][1][1] << '\n';
    else
        cout << DP[0][0][1] << ' ' << DP[1][0][1] + DP[1][1][1] % MOD << '\n';

    return 0;
}
