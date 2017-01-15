#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50010, NODE = 50005;

int N, M;
int answer[NMAX];
bool used_edge[2 * NMAX], used_vertex[NMAX];
vector<pair<int, int>> G[NMAX];

void Euler(int node) {
    used_vertex[node] = 1;
    for (const auto &it: G[node]) {
        if (used_edge[it.second])
            continue;
        used_edge[it.second] = 1;
        if (it.second <= M)
            answer[it.second] = node;
        Euler(it.first);
    }
}

int main() {
    assert(freopen("fotbal2.in", "r", stdin));
    assert(freopen("fotbal2.out", "w", stdout));

    int i, j, k;
    int x, y;

    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        G[x].push_back({y, i});
        G[y].push_back({x, i});
    }

    bool euler = 1;
    for (i = 1; i <= N; ++i)
        if (G[i].size() % 2) {
            euler = 0;
            break;
        }

    if (euler)
        cout << "0\n";
    else {
        cout << "2\n";
        int edge = M;
        for (i = 1; i <= N; ++i) {
            if (G[i].size() % 2) {
                G[i].push_back({NODE, ++edge});
                G[NODE].push_back({i, edge});
            }
        }
    }

    for (i = 1; i <= N; ++i)
        if (used_vertex[i] == 0)
            Euler(i);

    for (i = 1; i <= M; ++i)
        cout << answer[i] << '\n';

    return 0;
}
