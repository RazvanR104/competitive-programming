#include <bits/stdc++.h>

using namespace std;

const int NMAX = 810, inf = 0x3f3f3f3f;

int P, N, M;
int answer_1 = -1;
int Dmax[NMAX], D[NMAX][NMAX];
bool seen[NMAX];
vector<int> G[NMAX], C[NMAX];

void P1() {
    int i;
    queue<int> Q;
    Q.push(1);

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        seen[now] = 1;
        answer_1 = max(answer_1, Dmax[now]);

        for (i = 0; i < int(G[now].size()); ++i) {
            int node = G[now][i];
            if (seen[node] || Dmax[1] < C[now][i])
                continue;

            Q.push(node);
        }
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("dragoni.in", "r", stdin) != NULL);
    assert(freopen("dragoni.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> P >> N >> M;

    int x, y, d;
    for (i = 1; i <= N; ++i)
        cin >> Dmax[i];

    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> d;
        G[x].push_back(y);
        G[y].push_back(x);
        C[x].push_back(d);
        C[y].push_back(d);
    }

    if (P == 1) {
        P1();
        cout << answer_1 << '\n';
        return 0;
    }

    memset(D, inf, sizeof(D));

    D[1][1] = 0;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> Q;
    Q.push(make_tuple(0, 1, 1));

    while (!Q.empty()) {
        int cost, node, dragon;
        tie(cost, node, dragon) = Q.top();
        Q.pop();

        if (node == N) {
            cout << cost << '\n';
            return 0;
        }

        for (i = 0; i < int(G[node].size()); ++i) {
            if (Dmax[dragon] >= C[node][i] && D[G[node][i]][dragon] > cost + C[node][i]) {
                D[G[node][i]][dragon] = cost + C[node][i];
                Q.push(make_tuple(D[G[node][i]][dragon], G[node][i], dragon));
            }
        }

        if (dragon == node)
            continue;

        dragon = node;
        for (i = 0; i < int(G[node].size()); ++i) {
            if (Dmax[dragon] >= C[node][i] && D[G[node][i]][dragon] > cost + C[node][i]) {
                D[G[node][i]][dragon] = cost + C[node][i];
                Q.push(make_tuple(D[G[node][i]][dragon], G[node][i], dragon));
            }
        }
    }

	return 0;
}
