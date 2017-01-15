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

ifstream in("arb2.in");
ofstream out("arb2.out");

const int NMAX = 100010;
const int64 oo = 0x7fffffffffffffffLL;

int N;
int father[NMAX];
int64 res;
int64 L[NMAX], C[NMAX];
bool visited[NMAX];
vector<pair<int, pair<int, int> > > G[NMAX];

void DF(int node) {
    int i;
    visited[node] = true;

    for (i = 0; i < (int)G[node].size(); ++i) {
        if (visited[G[node][i].first]) continue;
        visited[G[node][i].first] = true;
        father[G[node][i].first] = node;
        DF(G[node][i].first);
        L[node] = max(L[node], L[G[node][i].first] + G[node][i].second.first);
        C[G[node][i].first] = min(C[G[node][i].first], (int64)G[node][i].second.second);
        C[node] += C[G[node][i].first];
    }

    if (L[node] == 0) {
        C[node] = oo;
        return;
    }

    for (i = 0; i < (int)G[node].size(); ++i)
        if (G[node][i].first != father[node])
            res += C[G[node][i].first] * (L[node] - L[G[node][i].first] - G[node][i].second.first);
}

int main() {
    int i, x, y, d, c;

    in >> N;
    for (i = 1; i < N; ++i) {
        in >> x >> y >> d >> c;
        G[x].push_back(make_pair(y, make_pair(d, c)));
        G[y].push_back(make_pair(x, make_pair(d, c)));
    }

    DF(1);
    out << res << '\n';

    in.close(), out.close();
    return 0;
}
