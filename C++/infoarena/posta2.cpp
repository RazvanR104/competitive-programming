#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;
typedef int64_t i64;

int N, M;
int tsize[NMAX], vcost[NMAX];
bool is[NMAX];
vector<pair<int, int>> G[NMAX], T[NMAX];

void DFS(int node, int from) {
    tsize[node] = is[node];
    for (const auto &it: G[node]) {
        if (it.first == from)
            continue;
        DFS(it.first, node);
        tsize[node] += tsize[it.first];
        if (tsize[it.first]) {
            T[node].push_back({it.first, it.second});
            T[it.first].push_back({node, it.second});
        }
    }
}

i64 DFS2(int node, int from) {
    i64 ret = 0;
    for (const auto &it: T[node]) {
        if (it.first == from)
            continue;
        ret += 2 * it.second;
        ret += DFS2(it.first, node);
    }
    return ret;
}

int main() {
    assert(freopen("posta2.in", "r", stdin));
    assert(freopen("posta2.out", "w", stdout));

    int i, j;
    int x, y, c;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N - 1; ++i) {
        scanf("%d %d %d", &x, &y, &c);
        G[x].push_back({y, c});
        G[y].push_back({x, c});
    }
    for (i = 1; i <= N; ++i)
        scanf("%d", &vcost[i]);
    for (i = 1; i <= M; ++i) {
        scanf("%d", &x);
        is[x] = 1;
    }

    DFS(x, -1);
    i64 cost = DFS2(x, -1);

    for (i = 1; i <= N; ++i)
        if (T[i].size())
            cost += 1ll * (T[i].size() - 1) * vcost[i];

    i64 answer = 1e18;
    for (i = 1; i <= N; ++i)
        if (T[i].size())
            answer = min(answer, cost - 1ll * (T[i].size() - 1) * vcost[i]);

    cout << answer << '\n';
    return 0;
}
