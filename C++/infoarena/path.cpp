#include <bits/stdc++.h>

using namespace std;

const int NMAX = 60;

int N, M, K;
int deg[NMAX], edges[NMAX][NMAX];
int DP[NMAX][NMAX];
vector<int> G[NMAX], T[NMAX];

inline int Node(char x) {
    if (x >= 'a' && x <= 'z')
        return x - 'a';
    return x - 'A' + 26;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("path.in", "r", stdin) != NULL);
    assert(freopen("path.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;
    char x, y;
    vector<int> values;

    cin >> N >> M >> K;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        x = Node(x), y = Node(y);
        edges[x][y] = 1;
        G[x].push_back(y);
        ++deg[y];
        values.push_back(x);
        values.push_back(y);
    }

    for (i = 1; i < NMAX; ++i)
        if (G[i].empty() && deg[i])
            DP[i][1] = 1;

    queue<int> Q;
    for (i = 0; i < NMAX; ++i)
        if (deg[i] == 0 && !G[i].empty())
            Q.push(i);

    vector<int> order;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        order.push_back(now);

        for (int node : G[now]) {
            --deg[node];
            if (deg[node] == 0)
                Q.push(node);
        }
    }

    int len = 1;
    for (i = N - 1; i >= 0; --i) {
        for (int node : G[order[i]]) {
            for (j = 1; j <= N; ++j) {
                DP[order[i]][j] += DP[node][j - 1];
                if (DP[order[i]][j])
                    len = max(len, j);
            }
        }
    }

    int next;
    int pos = len;
    vector<int> answer;

    int last = 0;
    for (i = 0; i < NMAX; ++i) {
        if (K > last && K <= last + DP[i][pos]) {
            K -= last;
            next = i;
            --pos;
            answer.push_back(i);
            break;
        }
        last += DP[i][pos];
    }

    while (pos) {
        sort(G[next].begin(), G[next].end());
        last = 0;
        for (i = 0; i < G[next].size(); ++i) {
            if (K > last && K <= last + DP[G[next][i]][pos]) {
                K -= last;
                --pos;
                answer.push_back(G[next][i]);
                next = G[next][i];
                break;
            }
            last += DP[G[next][i]][pos];
        }
    }


    for (int now : answer) {
        if (now >= 0 && now < 26)
            cout << char(now + 'a');
        else
            cout << char(now - 26 + 'A');
    }
    cout << '\n';

	return 0;
}
