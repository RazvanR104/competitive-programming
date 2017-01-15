#include <bits/stdc++.h>

using namespace std;

const int NMAX = 110;

int N, M;
int V[NMAX];
int sorted[NMAX], ind[NMAX], DP1[NMAX], DP2[NMAX];
vector<int> G[NMAX], GT[NMAX];

int main() {
    assert(freopen("pm2.in", "r", stdin));
    assert(freopen("pm2.out", "w", stdout));

    int i, j;

    cin >> N;
    for (i = 1; i <= N; ++i)
        cin >> V[i];

    for (i = 1; i <= N; ++i) {
        cin >> M;
        int x;
        for (j = 1; j <= M; ++j) {
            cin >> x;
            G[x].push_back(i);
            ++ind[i];
            GT[i].push_back(x);
        }
    }

    queue<int> Q;
    for (i = 1; i <= N; ++i)
        if (ind[i] == 0)
            Q.push(i);

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        sorted[++sorted[0]] = now;

        for (const int &next: G[now]) {
            --ind[next];
            if (ind[next] == 0)
                Q.push(next);
        }
    }

    for (i = 1; i <= N; ++i) {
        int now = sorted[i];
        int value = 0;
        for (const int &prev: GT[now])
            value = max(value, DP1[prev] + V[prev]);
        DP1[now] = value;
    }

    int answer = 0;
    for (i = 1; i <= N; ++i) {
        int now = sorted[i];
        answer = max(answer, DP1[now] + V[now]);
    }
    cout << answer << '\n';

    reverse(sorted + 1, sorted + N + 1);
    for (i = 1; i <= N; ++i) {
        int now = sorted[i];
        int value = answer;
        for (const int &prev: G[now])
            value = min(value, DP2[prev] - V[prev]);
        DP2[now] = value;
    }

    for (i = 1; i <= N; ++i)
        cout << DP1[i] << ' ' << DP2[i] - V[i] << '\n';

    return 0;
}
