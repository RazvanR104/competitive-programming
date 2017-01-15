#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010, KMAX = 15, inf = 0x3f3f3f3f;

int N, M, K;
int F[KMAX], D[NMAX], dleft[KMAX], dright[KMAX];
int cross[KMAX][KMAX], DP[KMAX][1 << KMAX];
vector<int> G[NMAX], C[NMAX];

void Dijkstra(int node) {
    memset(D, 0x3f, sizeof D);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    Q.push({0, node});
    D[node] = 0;

    while (!Q.empty()) {
        int cost, now;
        tie(cost, now) = Q.top();
        Q.pop();

        for (int i = 0; i < int(G[now].size()); ++i) {
            int next = G[now][i];
            int ncost = C[now][i];

            if (D[next] > D[now] + ncost) {
                D[next] = D[now] + ncost;
                Q.push({D[next], next});
            }
        }
    }
}

int main() {
    assert(freopen("ubuntzei.in", "r", stdin));
    assert(freopen("ubuntzei.out", "w", stdout));

    int i, j;

    cin >> N >> M >> K;

    for (i = 0; i < K; ++i)
        cin >> F[i];

    for (i = 1; i <= M; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        G[x].push_back(y);
        G[y].push_back(x);
        C[x].push_back(c);
        C[y].push_back(c);
    }

    Dijkstra(1);
    for (i = 0; i < K; ++i)
        dleft[i] = D[F[i]];

    if (K == 0) {
        cout << D[N] << '\n';
        return 0;
    }

    Dijkstra(N);
    for (i = 0; i < K; ++i)
        dright[i] = D[F[i]];

    for (i = 0; i < K; ++i) {
        Dijkstra(F[i]);
        for (j = 0; j < K; ++j)
            cross[i][j] = D[F[j]];
    }

    memset(DP, inf, sizeof DP);

    for (i = 0; i < K; ++i)
        DP[i][1 << i] = dleft[i];

    for (int mask = 1; mask < (1 << K); ++mask) {
        for (i = 0; i < K; ++i) {
            if (DP[i][mask] == inf)
                continue;
            for (j = 0; j < K; ++j)
                if ((mask & (1 << j)) == 0)
                    DP[j][mask ^ (1 << j)] = min(DP[j][mask ^ (1 << j)], DP[i][mask] + cross[i][j]);
        }
    }

    int answer = inf;
    for (i = 0; i < K; ++i)
        answer = min(answer, DP[i][(1 << K) - 1] + dright[i]);
    cout << answer << '\n';

    return 0;
}
