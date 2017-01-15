#include <bits/stdc++.h>

using namespace std;

const int NMAX = 150010;

int N, M;
int where[NMAX], top[NMAX], DP[2][NMAX];
bool vis[NMAX], lt[NMAX], rt[NMAX], ok[NMAX];
vector<int> G[NMAX], GT[NMAX], order, G2[NMAX], GT2[NMAX], comps[NMAX];

void DFS(int node) {
    vis[node] = 1;
    for (const int &it: G[node])
        if (vis[it] == 0)
            DFS(it);

    for (const int &it: GT[node])
        if (vis[it] == 0)
            DFS(it);
}

void DFM(int node) {
    vis[node] = 1;
    for (const int &it: G[node]) {
        if (vis[it])
            continue;
        DFM(it);
    }
    order.push_back(node);
}

void DFP(int node, int scc) {
    where[node] = scc;
    comps[scc].push_back(node);
    for (const int &it: GT[node]) {
        if (where[it])
            continue;
        DFP(it, scc);
    }
}

int main() {
    assert(freopen("drumuri5.in", "r", stdin));
    assert(freopen("drumuri5.out", "w", stdout));

    int i;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        GT[y].push_back(x);
    }

    DFS(1);
    for (i = 1; i <= N; ++i) {
        if (vis[i] == 0) {
            cout << "0\n";
            return 0;
        }
    }

    memset(vis, 0, sizeof vis);
    for (i = 1; i <= N; ++i)
        if (vis[i] == 0)
            DFM(i);

    int scc = 0;
    while (!order.empty()) {
        if (where[order.back()] == 0)
            DFP(order.back(), ++scc);
        order.pop_back();
    }

    for (i = 1; i <= N; ++i) {
        for (const int &it: G[i]) {
            if (where[i] != where[it]) {
                G2[where[i]].push_back(where[it]);
                GT2[where[it]].push_back(where[i]);
            }
        }
    }

    for (i = 1; i <= scc; ++i) {
        ++DP[0][i];

        int Min = -1;
        for (const int &it: G2[i]) {
            if (Min == -1 || Min > it)
                Min = it;
        }

        DP[0][Min] += DP[0][i];
    }

    for (i = scc; i >= 1; --i) {
        ++DP[1][i];

        int Max = -1;
        for (const int &it: GT2[i]) {
            if (Max == -1 || Max < it)
                Max = it;
        }

        DP[1][Max] += DP[1][i];
    }

    int answer = 0;
    for (i = 1; i <= scc; ++i)
        if (DP[0][i] + DP[1][i] == scc + 1) {
            answer += comps[i].size();
            for (const int &it: comps[i])
                ok[it] = 1;
        }

    cout << answer << '\n';
    for (i = 1; i <= N; ++i)
        if (ok[i])
            cout << i << ' ';
    cout << '\n';

    return 0;
}
