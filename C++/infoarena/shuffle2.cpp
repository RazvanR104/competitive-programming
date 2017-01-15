#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, MOD = 1e9 + 7;

int N, M;
int dmax = -1;
int DP[NMAX], distS[NMAX], distD[NMAX];
int from[2 * NMAX], to[2 * NMAX];
int fact[2 * NMAX], invfact[2 * NMAX];
int lsum[NMAX], edges[NMAX];
vector<int> G[NMAX], GT[NMAX], level[NMAX];

void BFS(int S, vector<int> G[], int dist[]) {
    queue<int> Q;
    Q.push(S);
    memset(dist, -1, (N + 1) * sizeof(int));
    dist[S] = 0;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (const int &it: G[now]) {
            if (dist[it] != -1)
                continue;
            dist[it] = dist[now] + 1;
            Q.push(it);
        }
    }
}

int FastExpo(int base, int expo) {
    int res = 1;
    while (expo) {
        if (expo & 1)
            res = 1ll * res * base % MOD;
        base = 1ll * base * base % MOD;
        expo >>= 1;
    }
    return res;
}

int main() {
    assert(freopen("shuffle2.in", "r", stdin));
    assert(freopen("shuffle2.out", "w", stdout));

    int i;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d %d", &from[i], &to[i]);
        G[from[i]].push_back(to[i]);
        GT[to[i]].push_back(from[i]);
    }

    BFS(1, G, distS);
    BFS(N, GT, distD);

    fact[0] = 1;
    for (i = 1; i <= M; ++i)
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    invfact[M] = FastExpo(fact[M], MOD - 2);
    for (i = M - 1; i >= 0; --i)
        invfact[i] = 1ll * invfact[i + 1] * (i + 1) % MOD;

    for (i = 1; i <= N; ++i) {
        level[distS[i]].push_back(i);
        dmax = max(dmax, distS[i]);
    }

    for (i = 1; i <= M; ++i)
        ++edges[distS[i]];
    for (i = dmax; i >= 0; --i)
        lsum[i] = lsum[i + 1] + edges[i];

    DP[N] = fact[lsum[distS[N]]];

    for (i = distS[N] - 1; i >= 0; --i) {
        for (const int &node: level[i]) {
            for (const int &next: G[node]) {
                if (distS[node] + 1 + distD[next] != distS[N])
                    continue;
                DP[node] += DP[next];
                if (DP[node] >= MOD)
                    DP[node] -= MOD;
            }
            DP[node] = 1ll * DP[node] * fact[lsum[distS[node]]] % MOD;
            DP[node] = 1ll * DP[node] * invfact[lsum[distS[node] + 1]] % MOD;
            DP[node] = 1ll * DP[node] * FastExpo(G[node].size(), MOD - 2) % MOD;
        }
    }

    cout << DP[1] << '\n';
    return 0;
}
