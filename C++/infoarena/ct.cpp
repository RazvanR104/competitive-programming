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

ifstream in("ct.in");
ofstream out("ct.out");

const int NMAX = 100010, LG2NMAX = 18;

int T, N, K;
int euler[2 * NMAX], level[2 * NMAX], RMQ[LG2NMAX][2 * NMAX], first[NMAX], node_level[NMAX], father[NMAX];

bool visited[NMAX], disconnected[NMAX];

struct LCA_Pairs {
    LCA_Pairs(const int &_x, const int &_y, const int &_LCA) : x(_x), y(_y), LCA(_LCA) {}
    bool operator>(const LCA_Pairs &rhs) const {
        return (node_level[LCA] > node_level[rhs.LCA]);
    }

    int x, y, LCA;
};

vector<int> G[NMAX];
vector<LCA_Pairs> pairs;

inline int lg2(int value) {
    int ret = -1;
    for ( ; value; value >>= 1, ++ret);
    return ret;
}

inline int pw2(const int &value) { return (1 << value); }

void DF(const int node, const int lvl) {
    visited[node] = true;
    euler[++euler[0]] = node;
    level[++level[0]] = lvl;
    first[node] = euler[0];
    node_level[node] = lvl;

    for (size_t it = 0; it < G[node].size(); ++it) {
        if (visited[G[node][it]]) continue;
        father[G[node][it]] = node;
        DF(G[node][it], lvl + 1);
        euler[++euler[0]] = node;
        level[++level[0]] = lvl;
    }
}

void Compute_RMQ() {
    int i, j;
    for (i = 1; i <= euler[0]; ++i) RMQ[0][i] = i;

    for (i = 1; pw2(i) <= euler[0]; ++i)
        for (j = 1; j + pw2(i) - 1 <= euler[0]; ++j) {
            if (level[RMQ[i - 1][j]] < level[RMQ[i - 1][j + pw2(i - 1)]]) RMQ[i][j] = RMQ[i - 1][j];
            else RMQ[i][j] = RMQ[i - 1][j + pw2(i - 1)];
    }
}

int LCA(int first_node, int second_node) {
    first_node = first[first_node], second_node = first[second_node];
    if (first_node > second_node) swap(first_node, second_node);

    int lgdist = lg2(second_node - first_node + 1);

    if (level[RMQ[lgdist][first_node]] < level[RMQ[lgdist][second_node - pw2(lgdist) + 1]]) return euler[RMQ[lgdist][first_node]];
    return euler[RMQ[lgdist][second_node - pw2(lgdist) + 1]];
}

void Disconnect(const int node) {
    disconnected[node] = true;
    for (size_t it = 0; it < G[node].size(); ++it)
        if (G[node][it] != father[node] && !disconnected[G[node][it]]) Disconnect(G[node][it]);
}

int main() {
    int i, x, y;

    for (in >> T; T; --T) {
        pairs.clear();
        memset(G, 0, sizeof(G));
        memset(visited, 0, sizeof(visited));
        memset(disconnected, 0, sizeof(disconnected));
        euler[0] = level[0] = 0;

        in >> N >> K;

        for (i = 1; i <= N - 1; ++i) {
            in >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }

        DF(1, 0);
        Compute_RMQ();

        while(K--) {
            in >> x >> y;
            int _LCA = LCA(x, y);
            pairs.push_back(LCA_Pairs(x, y, _LCA));
        }

        sort(pairs.begin(), pairs.end(), greater<LCA_Pairs>());

        int res = 0;
        for (size_t it = 0; it < pairs.size(); ++it) {
            if (!disconnected[pairs[it].x] && !disconnected[pairs[it].y]) Disconnect(pairs[it].LCA), ++res;
        }

        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
