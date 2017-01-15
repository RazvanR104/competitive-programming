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

#define st first
#define nd second

using namespace std;

typedef long long int64;

ifstream in("atac.in");
ofstream out("atac.out");

const int NMAX = 32010, LOG2NMAX = 20, inf = 0x3f3f3f3f;

int N, P, M, X, Y, A, B, C, D;
int RMQ[LOG2NMAX][2 * NMAX], euler[2 * NMAX], level[2 * NMAX], first[NMAX], cost[NMAX], father[NMAX], ancestor[LOG2NMAX][NMAX], best[LOG2NMAX][NMAX], node_level[NMAX];

vector<pair<int, int> > G[NMAX];

inline int lg2(int value) {
    int res = -1;
    for ( ; value; value >>= 1, ++res);
    return res;
}

inline int pw2(const int &value) { return (1 << value); }

void DF(const int node, const int lvl) {
    euler[++euler[0]] = node;
    level[++level[0]] = lvl;
    first[node] = euler[0];
    node_level[node] = lvl;

    for (size_t it = 0; it < G[node].size(); ++it) {
        father[G[node][it].st] = node;
        cost[G[node][it].st] = G[node][it].nd;
        DF(G[node][it].st, lvl + 1);
        euler[++euler[0]] = node;
        level[++level[0]] = lvl;
    }
}

void Compute_RMQ() {
    int i, j;
    for (i = 1; i <= euler[0]; ++i) RMQ[0][i] = i;

    for (i = 1; pw2(i) <= euler[0]; ++i)
        for (j = 1; j + pw2(i) - 1 <= euler[0]; ++j)
            if (level[RMQ[i - 1][j]] < level[RMQ[i - 1][j + pw2(i - 1)]]) RMQ[i][j] = RMQ[i - 1][j];
            else RMQ[i][j] = RMQ[i - 1][j + pw2(i - 1)];
}

inline int LCA(int first_node, int second_node) {
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
            best[i][j] = min(best[i - 1][ancestor[i - 1][j]], best[i - 1][j]);
        }
}

int min_cost(int node, int father) {
    int ret = inf;
    int lgdist = lg2(node_level[node] - node_level[father]), dist = node_level[node] - node_level[father];

    for (int bit = 0; bit <= lgdist; ++bit)
        if (pw2(bit) & dist) {
            ret = min(ret, best[bit][node]);
            node = ancestor[bit][node];
            dist -= pw2(bit);
        }

    return ret;
}

int main() {
    int i, j, cost;
    in >> N >> P >> M;

    for (i = 2; i <= N; ++i) {
        in >> j >> cost;
        G[j].push_back(make_pair(i, cost));
    }

    in >> X >> Y >> A >> B >> C >> D;

    DF(1, 0);
    Compute_RMQ();
    Compute_ancestor_best();

    for (i = 1; i <= P; ++i) {
        int _LCA, res;
        if (X != Y) _LCA = LCA(X, Y), res = min(min_cost(X, _LCA), min_cost(Y, _LCA));
        else res = 0;
        if (i > P - M) out << res << '\n';
        int _X = (1LL * X * A + 1LL * Y * B) % N + 1, _Y = (1LL * Y * C + 1LL * res * D) % N + 1;
        X =  _X, Y = _Y;
    }

    in.close(), out.close();
    return 0;
}
