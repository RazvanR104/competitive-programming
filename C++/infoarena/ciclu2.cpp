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

ifstream in("ciclu2.in");
ofstream out("ciclu2.out");

const int NMAX = 210;

int N, M, x, y;
bool visited[NMAX][NMAX];
vector<int> G[NMAX];

bool DF(int node, int curr_len, int len) {
    if (curr_len == len) {
        for (vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it)
            if (visited[node][*it] == false && *it == x) return true;
        return false;
    }

    for (vector<int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if (visited[node][*it]) continue;
        visited[node][*it] = visited[*it][node] = true;
        if (DF(*it, curr_len + 1, len)) return true;
        visited[node][*it] = visited[*it][node] = false;
    }
    return false;
}

int main() {
    int i, length;

    in >> N >> M;
    for (i = 1; i <= M; ++i) {
        in >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    in >> M;
    while(M--) {
        in >> x >> length;
        if (DF(x, 1, length)) out << "1\n";
        else out << "0\n";
        memset(visited, 0, sizeof(visited));
    }

    in.close(), out.close();
    return 0;
}
