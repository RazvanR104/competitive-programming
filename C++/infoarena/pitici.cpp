#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1024, inf = 0x7f7f7f7f;

int N, M, K;
int C[NMAX][NMAX], DP[NMAX][NMAX];
bool seen[NMAX];
vector<int> G[NMAX], order;

void DFS(int node) {
    seen[node] = 1;

    for (const int &next : G[node]) {
        if (seen[next])
            continue;
        DFS(next);
    }

    order.push_back(node);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("pitici.in", "r", stdin) != NULL);
    assert(freopen("pitici.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;

    cin >> N >> M >> K;

    int x, y, c;
    while (M--) {
        cin >> x >> y >> c;
        G[x].push_back(y);
        C[x][y] = c;
    }

    DFS(1);

    memset(DP, inf, sizeof(DP));
    DP[N][0] = 0;

    for (const int &node : order) {
        if (G[node].size() == 0)
            continue;

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> H;
        for (const int &_node : G[node])
            if (DP[_node][0] != inf)
                H.push(make_tuple(DP[_node][0] + C[node][_node], _node, 0));

        for (i = 0; i < K && !H.empty(); ++i) {
            int cost, where, index;
            tie(cost, where, index) = H.top();
            H.pop();
            DP[node][i] = cost;

            if (DP[where][index + 1] != inf)
                H.push(make_tuple(DP[where][index + 1] + C[node][where], where, index + 1));
        }
    }

    for (i = 0; i < K; ++i)
        cout << DP[1][i] << ' ';
    cout << '\n';

	return 0;
}
