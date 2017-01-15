#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, LG2NMAX = 20, inf = 0x3f3f3f3f;

int N, M, epos;
int euler[4 * NMAX], answer[NMAX];
int RMQ[LG2NMAX][4 * NMAX], cnt[NMAX];
vector<int> G[NMAX], pos[NMAX];
map<int, int> Next[NMAX], V[NMAX];

int main() {
    assert(freopen("sushi2.in", "r", stdin));
    assert(freopen("sushi2.out", "w", stdout));

    int i, j, k, x, y;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &k);
        for (j = 1; j <= k; ++j) {
            scanf("%d", &x);
            G[i].push_back(x);
        }
        G[i].push_back(G[i].front());
        for (j = 0; j < k; ++j)
            Next[i][G[i][j]] = G[i][j + 1];
    }

    euler[++epos] = 1;
    euler[++epos] = G[1][0];

    while (epos < 2 * N - 2) {
        euler[epos + 1] = Next[euler[epos]][euler[epos - 1]];
        ++epos;
    }
    memcpy(euler + epos + 1, euler + 1, epos * sizeof(int));
    epos = epos * 2 + 1;
    euler[epos] = 1;

    while (M--) {
        scanf("%d %d %d", &x, &y, &k);
        V[x][G[x][y - 1]] = max(V[x][G[x][y - 1]], k);
    }

    for (i = 1; i < epos; ++i) {
        pos[euler[i]].push_back(i);
        if (V[euler[i]].count(euler[i + 1]) == 0)
            RMQ[0][i] = inf;
        else
            RMQ[0][i] = i - V[euler[i]][euler[i + 1]];
    }

    for (i = 1; (1 << i) <= epos; ++i)
        for (j = 1; j + (1 << i) - 1 <= epos; ++j)
            RMQ[i][j] = min(RMQ[i - 1][j], RMQ[i - 1][j + (1 << (i - 1))]);

    for (i = 1; i <= N; ++i) {
        for (j = 1; j < pos[i].size(); ++j) {
            for (k = 0; (1 << k) <= pos[i][j] - pos[i][j - 1]; ++k);
            --k;
            answer[i] = max(answer[i], pos[i][j] - min(RMQ[k][pos[i][j - 1] + 1], RMQ[k][pos[i][j] - (1 << k) + 1]));
        }
    }

    for (i = 1; i <= N; ++i)
        cout << answer[i] << ' ';
    cout << '\n';

    return 0;
}
