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

ifstream in("concurs.in");
ofstream out("concurs.out");

const int NMAX = 32010, LG2NMAX = 16, inf = 0x7fffffff;

int N, M;
int res_x = inf, res_y = inf, res_sum = -inf;
int value[NMAX], euler[2 * NMAX], level[2 * NMAX], RMQ[LG2NMAX][2 * NMAX], first[NMAX];

vector<int> G[NMAX];

bool father[NMAX];

void DF(const int node, const int lvl) {
    euler[++euler[0]] = node;
    level[++level[0]] = lvl;
    first[node] = euler[0];

    for (size_t it = 0; it < G[node].size(); ++it) {
        DF(G[node][it], lvl + 1);
        euler[++euler[0]] = node;
        level[++level[0]] = lvl;
    }
}

inline int lg2(int value) {
    int ret = -1;
    for ( ; value; value >>= 1, ++ret);
    return ret;
}

inline int pw2(const int &value) { return (1LL << value); }

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

void update(const int &x, const int &y, const int &sum) {
    if (sum > res_sum)
        res_sum = sum, res_x = x, res_y = y;
    else if (sum == res_sum && x < res_x)
        res_x = x, res_y = y;
    else if (sum == res_sum && x == res_x && y < res_y)
        res_y = y;
}

int main() {
    int i, x, y, _LCA;

    in >> N >> M;

    for (i = 1; i <= N; ++i) in >> value[i];

    for (i = 1; i <= N - 1; ++i) {
        in >> x >> y;
        G[x].push_back(y);
        father[y] = true;
    }

    int root;
    for (i = 1; i <= N; ++i)
        if (!father[i]) {
            root = i;
            break;
        }

    DF(root, 0);
    Compute_RMQ();

    for (i = 1; i <= M; ++i) {
        in >> x >> y;
        _LCA = LCA(x, y);
        update(x, y, value[_LCA]);
    }

    out << res_sum << ' ' << res_x << ' ' << res_y << '\n';

    in.close(), out.close();
    return 0;
}
