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

ifstream fin("lca.in");
ofstream fout("lca.out");

const int NMAX = 100010, LOG = 18;

int N, M;
int RMQ[LOG][2 * NMAX], euler[2 * NMAX], first[NMAX], level[2 * NMAX];

bool visited[NMAX];

vector<int> G[NMAX];

inline int lg2(int value) {
    int res = -1;
    for ( ; value; value >>= 1, ++res);
    return res;
}

inline int pw2(const int &value) { return (1 << value); }

void DF(const int node, const int lvl) {
    visited[node] = true;
    euler[++euler[0]] = node;
    level[++level[0]] = lvl;
    first[node] = euler[0];

    for (size_t it = 0; it < G[node].size(); ++it) {
        if (visited[G[node][it]]) continue;
        DF(G[node][it], lvl + 1);
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

int main()
{
    int i, x, y;

    fin >> N >> M;

    for (i = 2; i <= N; ++i)
    {
        fin >> x;
        G[x].push_back(i);
    }

    DF(1, 0);

    Compute_RMQ();

    while(M--)
    {
        fin >> x >> y;
        fout << LCA(x, y) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
