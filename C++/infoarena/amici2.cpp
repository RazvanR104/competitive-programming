#include <bits/stdc++.h>

using namespace std;

const int NMAX = 21010;

int T, N, M;
int dist[NMAX];
vector<int> G[NMAX];

int main() {
    assert(freopen("amici2.in", "r", stdin));
    assert(freopen("amici2.out", "w", stdout));

    int x, y, i;

    for (scanf("%d", &T); T; --T) {
        scanf("%d %d", &N, &M);

        while (M--) {
            scanf("%d %d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }

        memset(dist, 0xff, sizeof dist);
        queue<int> Q;
        Q.push(1);
        dist[1] = 0;
        int Max = 0;

        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();

            for (const int &it: G[now]) {
                if (dist[it] != -1)
                    continue;
                dist[it] = dist[now] + 1;
                Max = max(Max, dist[it]);
                Q.push(it);
            }
        }

        int answer = 0;
        for ( ; (1 << answer) < Max; ++answer);

        cout << answer << '\n';

        for (i = 1; i <= N; ++i)
            G[i].clear();
    }

    return 0;
}
