#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300, inf = 0x3f3f3f3f;

int N, M, K;
int C[NMAX][NMAX], BF[NMAX], answer[NMAX];
bool inq[NMAX];
vector<int> G[NMAX], I[NMAX];

void DFS(int node, int from) {
    if (node <= K) {
        if (node == 1)
            answer[node] = BF[node];
        else
            answer[node] = BF[node] - BF[from];
    } else {
        if (from == 1)
            answer[node] = BF[node];
        else
            answer[node] = BF[node] - BF[from];
    }

    for (int _node : G[node])
        if (_node != from)
            DFS(_node, node);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("import.in", "r", stdin) != NULL);
    assert(freopen("import.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, x, y, c, d;

    cin >> N >> M >> K;
    for (i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> c >> d;
        if (d == 0) {
            C[x][y] = -c;
            I[x].push_back(y);
        } else {
            C[y][x] = c - 1;
            I[y].push_back(x);
        }
    }

    memset(BF, inf, sizeof(BF));
    BF[0] = 0;

    for (i = 1; i <= N; ++i)
        I[0].push_back(i);

    queue<int> Q;
    Q.push(0);
    inq[0] = 1;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        inq[now] = 0;

        for (int node : I[now]) {
            if (BF[node] > BF[now] + C[now][node]) {
                BF[node] = BF[now] + C[now][node];
                if (inq[node] == 0) {
                    inq[node] = 1;
                    Q.push(node);
                }
            }
        }
    }

    for (i = 1; i <= K; ++i)
        BF[i] = -BF[i];

    DFS(1, -1);

    for (i = 1; i <= N; ++i)
        cout << answer[i] << ' ';
    cout << '\n';

	return 0;
}
