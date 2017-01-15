#include <bits/stdc++.h>

using namespace std;

const int NMAX = 400;

int N, M;
int father[NMAX], used[NMAX];
vector<int> G[NMAX], T[NMAX];
int level[NMAX][NMAX], adj[NMAX][NMAX];

void DFS(int node, int curr_level) {
    used[node] = 1;
    vector<int> sons;

    for (const int &it: G[node]) {
        if (level[curr_level + 1][it])
            sons.push_back(it);
        else
            level[curr_level + 2][it] = 1;
    }

    for (const int &it: sons) {
        if (used[it])
            continue;
        father[it] = node;
        T[it].push_back(node);
        T[node].push_back(it);
        DFS(it, curr_level + 1);
    }
}

bool Check() {
    bool vis[NMAX] = {};
    vector<int> added;
    for (int i = 1; i <= N; ++i) {
        for (const int &it: added)
            vis[it] = 0;
        added.clear();
        queue<pair<int, int>> Q;

        Q.push({i, 0});
        vis[i] = 1;
        added.push_back(i);

        while (!Q.empty()) {
            int node, dist;
            tie(node, dist) = Q.front();
            Q.pop();

            if (dist != 0 && adj[i][node] == 0)
                return 0;

            if (dist < 2) {
                for (const int &it: T[node]) {
                    if (vis[it])
                        continue;
                    vis[it] = 1;
                    Q.push({it, dist + 1});
                    added.push_back(it);
                }
            }
        }
    }

    return 1;
}

int main() {
    assert(freopen("tree2.in", "r", stdin));
    assert(freopen("tree2.out", "w", stdout));

    int i;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x][y] = adj[y][x] = 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (int node = 1; node <= N; ++node) {
    for (const int &it: G[node]) {
        memset(used, 0, sizeof used);
        memset(father, 0, sizeof father);
        memset(level, 0, sizeof level);
        for (i = 1; i <= N; ++i)
            T[i].clear();

        T[it].push_back(node);
        T[node].push_back(it);

        father[it] = node;
        used[node] = 1;

        level[0][node] = 1;
        level[1][it] = 1;

        for (const int &it2: G[node]) {
            if (it2 == it)
                continue;
            level[2][it2] = 1;
        }

        DFS(it, 1);

        int cnt = 0;
        for (i = 1; i <= N; ++i)
            cnt += father[i] > 0;

        if (cnt == N - 1 && Check()) {
            for (i = 1; i <= N; ++i)
                if (father[i])
                    cout << i << ' ' << father[i] << '\n';
            return 0;
        }
    }
    }

    return 0;
}
