#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;

int N, K;
int nodes[NMAX], father[NMAX], level[NMAX], answer[NMAX];
vector<int> G[NMAX], order;

void DFS(int node, int from) {
    for (int next : G[node]) {
        if (next == from)
            continue;
        father[next] = node;
        level[next] = level[node] + 1;
        DFS(next, node);
    }
}

void Fill(int node, int from, int dist) {
    nodes[node] = 1;
    if (dist == 0)
        return;

    for (int now : G[node]) {
        if (now == from)
            continue;
        Fill(now, node, dist - 1);
    }
}

int Check(int dist) {
    memset(nodes, 0, sizeof(nodes));
    memset(answer, 0, sizeof(answer));
    int ret = 0;

    for (int now : order) {
        if (nodes[now])
            continue;
        for (int i = 0; i < dist && father[now]; ++i)
            now = father[now];

        answer[now] = 1;
        ++ret;

        Fill(now, -1, dist);
    }

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("salvare.in", "r", stdin) != NULL);
    assert(freopen("salvare.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, x, y;

    cin >> N >> K;
    for (i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, -1);
    for (i = 1; i <= N; ++i)
        order.push_back(i);
    sort(order.begin(), order.end(), [] (const int &lhs, const int &rhs) { return level[lhs] > level[rhs]; });

    int res = (1 << 10) - 1;
    for (int bit = (1 << 9); bit; bit >>= 1)
        if (Check(res - bit) <= K)
            res -= bit;

    cout << res << '\n';

    K -= Check(res);
    for (i = 1; i <= N; ++i) {
        if (answer[i])
            cout << i << ' ';
        else if (K) {
            --K;
            cout << i << ' ';
        }
    }

	return 0;
}
