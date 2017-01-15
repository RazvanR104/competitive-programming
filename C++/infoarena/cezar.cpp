#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 10010;

int N, K;
short cost[NMAX];
vector<short> G[NMAX];

int main() {
    freopen("cezar.in", "r", stdin);
    freopen("cezar.out", "w", stdout);

    int i, x, y;

    scanf("%d %d", &N, &K);
    for (i = 1; i < N; ++i) {
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    priority_queue<pair<short, short>> PQ;
    int answer = 0;
    for (i = 1; i <= N; ++i) {
        cost[i] = 1;
        if (G[i].size() == 1)
            PQ.push({-1, i});
    }

    while (N - K - 1) {
        auto it = PQ.top();
        int pos = it.second;
        PQ.pop();

        G[G[pos][0]].erase(find(G[G[pos][0]].begin(), G[G[pos][0]].end(), pos));
        answer += cost[pos];
        cost[G[pos][0]] += cost[pos];
        cost[pos] = -1;
        if (G[G[pos][0]].size() == 1) {
            PQ.push({-cost[G[pos][0]], G[pos][0]});
        }

        --N;
    }

    printf("%d\n", answer);
    return 0;
}
