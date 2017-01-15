#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <list>
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

ifstream in("ciclueuler.in");
ofstream out("ciclueuler.out");

const int NMAX = 100010;

int N, M;
int deg[NMAX];

bool visited[NMAX];

list<int> G[NMAX], res;
stack<int> S;

void DF(const int node) {
    visited[node] = true;
    for (list<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if (visited[*it]) continue;
        DF(*it);
    }
}

void _erase(const int &node, const int &_node) {
    G[node].pop_front();

    for (list<int>::iterator it = G[_node].begin(); it != G[_node].end(); ++it)
        if (*it == node) {
            G[_node].erase(it);
            break;
        }
}

void solve() {
    S.push(1);

    while(!S.empty()) {
        int node = S.top(), _node;
        S.pop();

        while(G[node].size()) {
            _node = G[node].front();
            _erase(node, _node);
            S.push(node);
            node = _node;
        }

        res.push_back(node);
    }
}

int main() {
    int i, x, y;

    in >> N >> M;

    for (i = 1; i <= M; ++i) {
        in >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);

        ++deg[x], ++deg[y];
    }

    DF(1);

    for (i = 1; i <= N; ++i)
        if (deg[i] % 2 || visited[i] == false) {
            out << -1 << '\n';
            in.close(), out.close();
            return 0;
        }

    solve();

    res.pop_back();
    for (list<int>::iterator it = res.begin(); it != res.end(); ++it)
        out << *it << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
