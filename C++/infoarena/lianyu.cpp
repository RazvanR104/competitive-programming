#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3010, inf = 0x3f3f3f3f;

int N, M, K;
int Time, biconn;
int cost[NMAX], DFN[NMAX], lowlink[NMAX], ssize[NMAX];
int DP[2 * NMAX][NMAX];
bool used[NMAX];
stack<pair<int, int>> E;
vector<int> G[NMAX], T[2 * NMAX];

void ProcessEdges(int x, int y) {
    int from, to;
    ++biconn;
    do {
        tie(from, to) = E.top();
        E.pop();
        T[biconn].push_back(to);
        T[to].push_back(biconn);
    } while (from != x || to != y);
    T[biconn].push_back(from);
    T[from].push_back(biconn);
}

void Biconnected(int node) {
    DFN[node] = lowlink[node] = Time++;
    used[node] = 1;

    for (const int &it: G[node]) {
        if (used[it] == 0) {
            E.push({node, it});
            Biconnected(it);
            lowlink[node] = min(lowlink[node], lowlink[it]);

            if (lowlink[it] >= DFN[node])
                ProcessEdges(node, it);
        } else
            lowlink[node] = min(lowlink[node], DFN[it]);
    }
}

void DFS_DP(int node, int from) {
    if (node <= N)
        ssize[node] = 1;
    else ssize[node] = 0;

    for (const int &it: T[node]) {
        if (it == from)
            continue;
        DFS_DP(it, node);
        ssize[node] += ssize[it];
    }

    int now = 0, i, j;
    for (const int &it: T[node]) {
        if (it == from)
            continue;
        now += ssize[it];

        for (i = min(K, now); i >= 1; --i)
            for (j = min(i, ssize[it]); j >= 1; --j)
                DP[node][i] = min(DP[node][i], DP[node][i - j] + DP[it][j]);
    }

    if (node <= N)
        for (i = min(K, ssize[node]); i >= 1; --i)
            DP[node][i] = DP[node][i - 1] + cost[node];

}

int main() {
    assert(freopen("lianyu.in", "r", stdin));
    assert(freopen("lianyu.out", "w", stdout));

    int i, j, x, y;

    scanf("%d %d %d", &N, &M, &K);
    for (i = 1; i <= N; ++i)
        scanf("%d", &cost[i]);

    for (i = 1; i <= M; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    biconn = N;
    Biconnected(1);

    memset(DP, inf, sizeof DP);
    for (i = 1; i <= biconn; ++i)
        DP[i][0] = 0;

    DFS_DP(1, -1);

    int answer = inf;
    for (i = 1; i <= biconn; ++i)
        answer = min(answer, DP[i][K]);

    cout << answer << '\n';
    return 0;
}
