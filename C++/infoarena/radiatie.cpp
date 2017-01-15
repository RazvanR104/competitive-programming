#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long int64;

ifstream in("radiatie.in");
ofstream out("radiatie.out");

const int NMAX = 15010, LG2NMAX = 16, inf = 0x3f3f3f3f;

int N, M, K;
int disjoint[NMAX], height[NMAX], RMQ[LG2NMAX][2 * NMAX], ancestor[LG2NMAX][NMAX], best[LG2NMAX][NMAX], euler[2 * NMAX], level[2 * NMAX], first[NMAX], father[NMAX], cost[NMAX], node_level[NMAX];

bool visited[NMAX];

struct Edge {
    Edge(int _x, int _y, int _c) : x(_x), y(_y), c(_c) {}
    bool operator<(const Edge &rhs) const {
        return (c < rhs.c);
    }

    int x, y, c;
};

vector<pair<int, int> > G[NMAX];
vector<Edge> edges;

int find_root(int pos) {
    int ret;
    for (ret = pos; ret != disjoint[ret]; ret = disjoint[ret]);

    while(pos != disjoint[pos]) {
        int _pos = disjoint[pos];
        disjoint[pos] = ret;
        pos = _pos;
    }

    return ret;
}

void unite(int first_root, int second_root) {
    if (height[first_root] > height[second_root]) disjoint[second_root] = first_root;
    else disjoint[first_root] = second_root;

    if (height[first_root] == height[second_root]) ++height[second_root];
}

void DF(const int node, const int lvl) {
    visited[node] = true;
    euler[++euler[0]] = node;
    level[++level[0]] = lvl;
    first[node] = euler[0];
    node_level[node] = lvl;

    for (size_t it = 0; it < G[node].size(); ++it) {
        if (visited[G[node][it].first]) continue;
        father[G[node][it].first] = node;
        cost[G[node][it].first] = G[node][it].second;
        DF(G[node][it].first, lvl + 1);
        euler[++euler[0]] = node;
        level[++level[0]] = lvl;
    }
}

inline int lg2(int value) {
    int ret = -1;
    for ( ; value; value >>= 1, ++ret);
    return ret;
}

inline int pw2(const int &value) { return (1 << value); }

void Compute_RMQ() {
    int i, j;
    for (i = 1; i <= euler[0]; ++i) RMQ[0][i] = i;

    for (i = 1; pw2(i) <= euler[0]; ++i)
        for (j = 1; j + pw2(i) - 1 <= euler[0]; ++j)
            if (level[RMQ[i - 1][j]] < level[RMQ[i - 1][j + pw2(i - 1)]]) RMQ[i][j] = RMQ[i - 1][j];
            else RMQ[i][j] = RMQ[i - 1][j + pw2(i - 1)];
}

int LCA(int first_node, int second_node) {
    first_node = first[first_node], second_node = first[second_node];
    if (first_node > second_node) swap(first_node, second_node);
    int lgdist = lg2(second_node - first_node + 1);

    if (level[RMQ[lgdist][first_node]] < level[RMQ[lgdist][second_node - pw2(lgdist) + 1]]) return euler[RMQ[lgdist][first_node]];
    return euler[RMQ[lgdist][second_node - pw2(lgdist) + 1]];
}

void Compute_ancestor_best() {
    int i, j;
    for (i = 1; i <= N; ++i) ancestor[0][i] = father[i], best[0][i] = cost[i];

    for (i = 1; pw2(i) < N; ++i)
        for (j = 1; j <= N; ++j) {
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];
            best[i][j] = max(best[i - 1][j], best[i - 1][ancestor[i - 1][j]]);
        }
}

int max_dist(int node, int LCA) {
    int dist = node_level[node] - node_level[LCA];
    int lgdist = lg2(dist);
    int ret = -inf;

    for (int bit = 0; bit <= lgdist; ++bit)
        if (dist & pw2(bit)) {
            ret = max(ret, best[bit][node]);
            node = ancestor[bit][node];
        }

    return ret;
}

int main() {
    int i, x, y, c;

    in >> N >> M >> K;

    for (i = 1; i <= M; ++i) {
        in >> x >> y >> c;
        edges.push_back(Edge(x, y, c));
    }
    sort(edges.begin(), edges.end());

    for (i = 1; i <= N; ++i) disjoint[i] = i;

    for (i = 0; i < M; ++i) {
        int first_root = find_root(edges[i].x), second_root = find_root(edges[i].y);
        if (first_root == second_root) continue;
        unite(first_root, second_root);
        G[edges[i].x].push_back(make_pair(edges[i].y, edges[i].c));
        G[edges[i].y].push_back(make_pair(edges[i].x, edges[i].c));
    }

    for (i = 1; i <= N; ++i)
        if (!visited[i]) DF(i, 0);
    Compute_RMQ();
    Compute_ancestor_best();

    while(K--) {
        in >> x >> y;
        int _LCA = LCA(x, y);
        out << max(max_dist(x, _LCA), max_dist(y, _LCA)) << '\n';
    }

    in.close(), out.close();
    return 0;
}
