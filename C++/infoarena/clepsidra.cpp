#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, MOD = 666013;

int N, M;
vector<int> G[NMAX];

int DFN[NMAX], lowlink[NMAX], answer[NMAX];

int FastExpo(int base, int expo) {
    int answer = 1;
    while (expo) {
        if (expo & 1)
            answer = 1ll * answer * base % MOD;
        expo >>= 1;
        base = 1ll * base * base % MOD;
    }
    return answer;
}

void DFS(int node, int from, int level) {
    int conex = 0;
    DFN[node] = lowlink[node] = level;

    for (const int &it: G[node]) {
        if (it == from)
            continue;
        if (DFN[it] == -1) {
            DFS(it, node, level + 1);
            lowlink[node] = min(lowlink[node], lowlink[it]);

            if (lowlink[it] >= DFN[node])
                ++conex;

        } else
            lowlink[node] = min(lowlink[node], DFN[it]);
    }

    if (from != -1)
        ++conex;

    answer[node] = FastExpo(2, conex) - 2;
    if (answer[node] < 0)
        answer[node] += MOD;
}

int main() {
    assert(freopen("clepsidra.in", "r", stdin));
    assert(freopen("clepsidra.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    memset(DFN, 0xff, sizeof DFN);
    DFS(1, -1, 0);

    for (i = 1; i <= N; ++i)
        cout << answer[i] << '\n';

    return 0;
}
