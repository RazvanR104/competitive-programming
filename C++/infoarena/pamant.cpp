#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, M, timenow;
int DFN[NMAX], lowlink[NMAX];
vector<int> G[NMAX], critical, num;

void DFS(int node, int root) {
    DFN[node] = lowlink[node] = ++timenow;
    int cnt = 0;

    for (const int &it: G[node]) {
        if (DFN[it] == 0) {
            DFS(it, root);
            lowlink[node] = min(lowlink[node], lowlink[it]);
            if (lowlink[it] >= DFN[node])
                ++cnt;
        } else
            lowlink[node] = min(lowlink[node], DFN[it]);
    }

    if (node == root && cnt > 1)
        critical.push_back(node);
    else if (node != root && cnt > 0)
        critical.push_back(node);
}

int main() {
    assert(freopen("pamant.in", "r", stdin));
    assert(freopen("pamant.out", "w", stdout));

    int i, j;
    int x, y;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (i = 1; i <= N; ++i)
        if (DFN[i] == 0) {
            DFS(i, i);
            num.push_back(i);
        }

    cout << num.size() << '\n';
    for (const int &it: num)
        cout << it << ' ';
    cout << '\n' << critical.size() << '\n';

    sort(critical.begin(), critical.end());
    for (const int &it: critical)
        cout << it << ' ';
    cout << '\n';

    return 0;
}
