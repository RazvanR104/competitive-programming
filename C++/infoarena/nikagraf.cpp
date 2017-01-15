#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, LG2NMAX = 18;

int N, Q, len1, len2;
int cx, cy, ccost;
int euler[2 * NMAX], father[NMAX], pos[NMAX], first[NMAX], last[NMAX], level[NMAX];
int RMQ[LG2NMAX][2 * NMAX];
int BIT[2 * NMAX];
vector<pair<int, int>> G[NMAX];

struct Edge {
    int x, y, c, son;
} E[NMAX];

int Query(int pos) {
    int ret = 0;
    for ( ; pos; pos -= pos & -pos)
        ret += BIT[pos];
    return ret;
}

void Update(int pos, int value) {
    for ( ; pos <= len2; pos += pos & -pos)
        BIT[pos] += value;
}

void BuildBIT() {
    for (int i = 1; i <= N; ++i) {
        Update(first[i], E[father[i]].c);
        Update(last[i], -E[father[i]].c);
    }
}

void DFS(int node, int from) {
    RMQ[0][++len1] = node;
    euler[++len2] = node;
    pos[node] = len1;
    first[node] = len2;

    for (const auto &it: G[node]) {
        int next, edge;
        tie(next, edge) = it;
        if (it.first == from)
            continue;
        E[edge].son = next;
        father[next] = edge;
        level[next] = level[node] + 1;
        DFS(next, node);
        RMQ[0][++len1] = node;
    }

    euler[++len2] = node;
    last[node] = len2;
}

void BuildRMQ() {
    for (int i = 1; (1 << i) <= len1; ++i)
        for (int j = 1; j + (1 << i) - 1 <= len1; ++j)
            RMQ[i][j] = level[RMQ[i - 1][j]] < level[RMQ[i - 1][j + (1 << (i - 1))]] ? RMQ[i - 1][j] : RMQ[i - 1][j + (1 << (i - 1))];
}

int lg2(int value) {
    int ret = -1;
    while (value) {
        ++ret;
        value >>= 1;
    }
    return ret;
}

int LCA(int x, int y) {
    if (pos[x] > pos[y])
        swap(x, y);
    int lgdist = lg2(pos[y] - pos[x] + 1);
    return level[RMQ[lgdist][pos[x]]] < level[RMQ[lgdist][pos[y] - (1 << lgdist) + 1]] ? RMQ[lgdist][pos[x]] : RMQ[lgdist][pos[y] - (1 << lgdist) + 1];
}

int Distance(int x, int y) {
    if (first[x] > first[y])
        swap(x, y);
    return Query(first[y]) - Query(first[x] - 1) - E[father[x]].c;
}

bool Intersect(int a1, int b1, int a2, int b2) {

}

int main() {
    assert(freopen("nikagraf.in", "r", stdin));
    assert(freopen("nikagraf.out", "w", stdout));

    int i, j;

    cin >> N >> Q;
    for (i = 1; i < N; ++i) {
        cin >> E[i].x >> E[i].y >> E[i].c;
        G[E[i].x].push_back({E[i].y, i});
        G[E[i].y].push_back({E[i].x, i});
    }
    cin >> cx >> cy >> ccost;

    DFS(1, -1);
    BuildRMQ();
    BuildBIT();

    int type, a, b, c, m;
    int lcacycle = LCA(cx, cy);
    while (Q--) {
        cin >> type;
        if (type == 0) {
            cin >> a >> b;
            int lca = LCA(a, b);
            int answer = 2e9;

            if (lca != a && lca != b)
                answer = min(answer, Distance(a, lca) + Distance(b, lca));
            else
                answer = min(answer, Distance(a, b));

            cout << answer << '\n';
        } else if (type == 1) {
            cin >> m;
            cin >> E[m].c;
            int value = Query(first[E[m].son]) - Query(first[E[m].son] - 1);
            value = -value + E[m].c;
            Update(first[E[m].son], value);
            Update(last[E[m].son], -value);
        } else {
            cin >> cx >> cy >> ccost;
            lcacycle = LCA(cx, cy);
        }
    }

    return 0;
}
