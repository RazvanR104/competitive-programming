#include <bits/stdc++.h>

using namespace std;

const int NMAX = 30010, MMAX = 90010, KMAX = 120010;
const int64_t inf = 0x3f3f3f3f3f3f3f3fLL;

struct Flight {
    int x, t_dec, y, t_ater, p;
    bool operator<(const Flight &rhs) const {
        return t_ater < rhs.t_ater;
    }
} F[MMAX];

vector<int> G[NMAX], GT[NMAX];
set<pair<int, int>> Q[NMAX];
int N, M, K;
int64_t D[MMAX], answer[KMAX];

int main() {
    assert(freopen("avioane2.in", "r", stdin));
    assert(freopen("avioane2.out", "w", stdout));

    int i, j;

    scanf("%d %d %d", &N, &M, &K);
    for (i = 1; i <= M; ++i)
        scanf("%d %d %d %d %d", &F[i].x, &F[i].t_dec, &F[i].y, &F[i].t_ater, &F[i].p);
    sort(F + 1, F + M + 1);
    for (i = 1; i <= M; ++i) {
        G[F[i].x].push_back(i);
        GT[F[i].y].push_back(i);
    }

    for (i = 1; i <= K; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        Q[x].insert({y, i});
    }

    memset(D, 0x3f, sizeof D);
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> PQ;
    for (const int &it: G[1]) {
        PQ.push({F[it].p, it});
        D[it] = F[it].p;
    }

    while (!PQ.empty()) {
        int64_t curr;
        int flight;
        tie(curr, flight) = PQ.top();
        PQ.pop();

        for (const int &it: G[F[flight].y]) {
            if (F[it].t_dec >= F[flight].t_ater && D[it] > curr + F[it].p) {
                D[it] = curr + F[it].p;
                PQ.push({D[it], it});
            }
        }
    }

    for (const auto &it: Q[1])
        answer[it.second] = 0;

    for (i = 2; i <= N; ++i) {
        int64_t Min = inf;

        j = 0;
        for (const auto &it: Q[i]) {
            while (j < int(GT[i].size()) && F[GT[i][j]].t_ater <= it.first)
                Min = min(Min, D[GT[i][j++]]);

            if (Min == inf)
                answer[it.second] = -1;
            else
                answer[it.second] = Min;
        }
    }

    for (i = 1; i <= K; ++i)
        cout << answer[i] << '\n';

    return 0;
}
